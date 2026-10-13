<?php require_once 'config.php'; 
session_start();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

    <!-- Bootstrap CSS -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.5/dist/css/bootstrap.min.css" integrity="sha384-SgOJa3DmI69IUzQ2PVdRZhwQ+dy64/BUtbMJw1MZ8t5HZApcHrRKUc4W0kG879m7" crossorigin="anonymous">
    <!-- You can change the title to reflect the page contents. -->
</head>
<body>

<!-- Navigation Bar -->
<nav class="navbar navbar-expand-lg navbar-light bg-light">
    <!-- Blocks logo button goes to index.php -->

    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav"
            aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
    </button>

    <div class="collapse navbar-collapse" id="navbarNav">
        <ul class="navbar-nav mr-auto">
            <li class="nav-item">
                <a class="nav-link" href="index.php">Home</a>
            </li>
            <?php if (!isset($_SESSION["email_address"])) : ?>
                <li class="nav-item">
                    <a class="nav-link" href="register.php">Registration</a>
                </li>
            <?php endif; ?>
            <?php if (isset($_SESSION["email_address"])) : ?>
                <li class="nav-item">
                    <a class="nav-link" href="logout.php">Logout</a>
                </li>

            <?php endif; ?>
          
            <?php if (isset($_SESSION["email_address"])) : ?>
                <li class="nav-item">
                    <a class="nav-link" href="logout.php" title="Logout">Logout</a>
                </li>
            <?php endif; ?>
        </ul>
        <?php if (isset($_SESSION['name'])) : ?>
            <span class="navbar-text text-success">Welcome, <?php echo $_SESSION['name']; ?></span>
        <?php else : ?>
            <a class="nav-link text-danger" href="login.php">Log In</a>
        <?php endif; ?>
    </div>
</nav>