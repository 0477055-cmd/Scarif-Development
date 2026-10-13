<?php
include "template.php"; 

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $email = $_POST['email_address'];
    $password = $_POST['password'];

    // Vulnerable: Directly embedding user input into SQL
    $sql = "SELECT * FROM users WHERE email_address = '$email' AND password = '$password'";
    $stmt = $pdo->query($sql);
    $user = $stmt->fetch();

    if ($user) {
        echo "Login successful!";
    } else {
        echo "Invalid credentials.";
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>

</head>
<body class="bg-light">
<div class="container mt-5">
    <div class="card shadow-sm">
        <div class="card-header bg-primary text-white">Login</div>
        <div class="card-body">
            <?php if ($error): ?>
                <div class="alert alert-danger"><?= $error ?></div>
            <?php endif; ?>
            <form method="POST" action="">
                <div class="mb-3">
                    <label for="email_address" class="form-label">Email address</label>
                    <input type="email" class="form-control" name="email_address" required>
                </div>
                <div class="mb-3">
                    <label for="password" class="form-label">Password</label>
                    <input type="password" class="form-control" name="password" required>
                </div>
                <button type="submit" class="btn btn-success">Login</button>
            </form>
        </div>
    </div>
</div>
</body>
</html>
