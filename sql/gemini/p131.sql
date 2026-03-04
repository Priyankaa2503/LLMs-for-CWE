-- Conceptual logic for a stored procedure
CREATE PROCEDURE GetRenderedHome (IN user_name VARCHAR(255))
BEGIN
    -- Fetching the template from the 'environment' table
    SELECT REPLACE(template_content, '{{name}}', user_name) 
    FROM environment_templates 
    WHERE template_name = 'home_page';
END;

-- The "home" function equivalent
CALL GetRenderedHome('Guest');