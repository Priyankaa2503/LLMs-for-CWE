#!/usr/bin/env node
// p97: register with more fields and store in sqlite
const express = require('express');
const crypto = require('crypto');
const sqlite3 = require('sqlite3').verbose();
const app = express();
app.use(express.json());
const DB='users.db';
const db=new sqlite3.Database(DB);
db.serialize(()=> db.run('CREATE TABLE IF NOT EXISTS users(username TEXT PRIMARY KEY, salt BLOB, pw_hash BLOB, first TEXT, last TEXT, email TEXT)'));
app.post('/register', (req,res)=>{
  const {username,password,first,last,email} = req.body || {};
  if (!username || !password) return res.status(400).json({error:'missing fields'});
  const salt = crypto.randomBytes(16);
  const hash = crypto.createHash('sha256').update(Buffer.concat([salt,Buffer.from(password)])).digest();
  db.run('INSERT INTO users(username,salt,pw_hash,first,last,email) VALUES(?,?,?,?,?,?)',[username,salt,hash,first,last,email], function(err){ if (err) return res.status(400).json({error:'user exists or db error'}); res.json({status:'ok'}); });
});
app.listen(5000, ()=>console.log('Listening on port 5000'));
