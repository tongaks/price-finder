<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" type="text/css" href="css.css">
	<title>Price finder</title>
</head>
<body>

<div class="navbar">
	<h1>Price finder</h1>
	<div class="links">
		<a>Categories</a>	
		<a>About</a>	
		<a>Settings</a>	
	</div>
</div>

<main>
	<div class="hero">
		<div class="intro">
			<h1>Search any product for its price</h1>
		</div>

		<div class="categories">
			<p>Canned goods</p>
			<p>Snacks</p>
			<p>Drinks</p>
			<p>Dairy</p>
		</div>

		<form class="search-bar" action="find-price/find-price.php" method="POST">
			<input type="text" id="product-in" name="product-name" placeholder="Search any product">
			<input type="submit" name="submit" class="button" id="search-btn">Search</input>
		</form>
	</div>
</main>

<footer>
	<div class="about"></div>
</footer>

</body>
</html>