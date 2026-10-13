<?php
// config.php

// Path to the SQLite database file in the root directory
define('DB_PATH', './site.db');

try {
    // Create (connect to) SQLite database in file
    $pdo = new PDO('sqlite:' . DB_PATH);
    // Set error mode to exceptions
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    die('Connection failed: ' . $e->getMessage());
}
?>