// Java Spring Boot - Secure Unsubscribe Endpoint
package com.example.api.controller;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Date;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.util.Base64;
import java.util.regex.Pattern;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.http.ResponseEntity;
import org.springframework.http.HttpStatus;
import org.springframework.beans.factory.annotation.Value;
import com.zaxxer.hikari.HikariDataSource;

@RestController
public class p143_fc {
    
    private static final long TOKEN_MAX_AGE_MS = 86400000L; // 24 hours
    private static final String EMAIL_REGEX = "^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+\\.[A-Z|a-z]{2,}$";
    private static final Pattern emailPattern = Pattern.compile(EMAIL_REGEX);
    
    @Value("${app.secret-key}")
    private String secretKey;
    
    private final HikariDataSource dataSource;
    
    public UnsubscribeController(HikariDataSource dataSource) {
        this.dataSource = dataSource;
    }
    
    /**
     * Secure unsubscribe endpoint using HMAC-signed tokens.
     * GET /unsubscribe?token=<signed_token>
     */
    @GetMapping("/unsubscribe")
    public ResponseEntity<UnsubscribeResponse> unsubscribe(
            @RequestParam(value = "token", defaultValue = "") String token) {
        
        // Empty token - generic response
        if (token == null || token.trim().isEmpty()) {
            return ResponseEntity.ok(new UnsubscribeResponse("ok"));
        }
        
        // Verify token signature and expiration
        String email = verifyToken(token.trim());
        if (email == null) {
            // Invalid/expired token - generic response
            return ResponseEntity.ok(new UnsubscribeResponse("ok"));
        }
        
        // Normalize and validate email
        email = normalizeEmail(email);
        if (email == null) {
            return ResponseEntity.ok(new UnsubscribeResponse("ok"));
        }
        
        try {
            processUnsubscribe(email);
        } catch (Exception e) {
            // Log but don't expose DB errors
            e.printStackTrace();
        }
        
        // Always return same response - prevents enumeration
        return ResponseEntity.ok(new UnsubscribeResponse("ok"));
    }
    
    private String verifyToken(String token) {
        try {
            String[] parts = token.split("\\.", 2);
            if (parts.length != 2) return null;
            
            String encodedData = parts[0];
            String signature = parts[1];
            
            // Verify HMAC signature
            String computedSignature = generateSignature(encodedData);
            if (!constantTimeEquals(signature, computedSignature)) {
                return null;
            }
            
            // Decode payload
            String payload = new String(Base64.getUrlDecoder().decode(encodedData));
            String[] payloadParts = payload.split(":", 2);
            if (payloadParts.length != 2) return null;
            
            long timestamp = Long.parseLong(payloadParts[0]);
            String email = payloadParts[1];
            
            // Check expiration
            if (System.currentTimeMillis() - timestamp > TOKEN_MAX_AGE_MS) {
                return null;
            }
            
            return email;
        } catch (Exception e) {
            return null;
        }
    }
    
    private String generateSignature(String data) throws Exception {
        Mac mac = Mac.getInstance("HmacSHA256");
        mac.init(new SecretKeySpec(secretKey.getBytes(), "HmacSHA256"));
        byte[] digest = mac.doFinal(data.getBytes());
        return Base64.getUrlEncoder().withoutPadding().encodeToString(digest);
    }
    
    private boolean constantTimeEquals(String a, String b) {
        byte[] aBytes = a.getBytes();
        byte[] bBytes = b.getBytes();
        int result = 0;
        for (int i = 0; i < aBytes.length && i < bBytes.length; i++) {
            result |= aBytes[i] ^ bBytes[i];
        }
        result |= aBytes.length ^ bBytes.length;
        return result == 0;
    }
    
    private String normalizeEmail(String email) {
        if (email == null) return null;
        email = email.trim().toLowerCase();
        if (email.length() > 254 || !emailPattern.matcher(email).matches()) {
            return null;
        }
        return email;
    }
    
    private void processUnsubscribe(String email) throws Exception {
        try (Connection conn = dataSource.getConnection()) {
            // Check if subscribed using parameterized query
            String checkSql = "SELECT id FROM subscriptions WHERE email = ? AND subscribed = 1";
            try (PreparedStatement pstmt = conn.prepareStatement(checkSql)) {
                pstmt.setString(1, email);
                try (ResultSet rs = pstmt.executeQuery()) {
                    if (rs.next()) {
                        // Update subscription status
                        String updateSql = "UPDATE subscriptions SET subscribed = 0 WHERE email = ?";
                        try (PreparedStatement updateStmt = conn.prepareStatement(updateSql)) {
                            updateStmt.setString(1, email);
                            updateStmt.executeUpdate();
                        }
                        // Trigger external mailing list unsubscribe
                        // mailingListService.unsubscribe(email);  // Pseudo-code
                    }
                }
            }
        }
    }
    
    static class UnsubscribeResponse {
        public String status;
        
        public UnsubscribeResponse(String status) {
            this.status = status;
        }
    }
}