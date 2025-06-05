import puppeteer from "puppeteer"

const getPrice = async()=> {

// start puppeteer
const browser = await puppeteer.launch({
	headless: true, defaultViewport: null
});

// open new browser page
const page = await browser.newPage();

// get the page
let url = "https://puregold.com.ph/index.php/pgcatalog/product/view/category/SNACKS/subcategory/CHIPS,%20NUTS%20&%20CORN/title/PIKNIK%20SHOESTRING%20POTATOES%20ORIGINAL%204%20OZ%20/barcode/74923405198";
await page.goto(url, {
	waitUntil: "domcontentloaded"
});

// scrape the price
const price = await page.evaluate(()=> {
    const price_tag = document.querySelector(".price").innerText;
    return price_tag;
})

const product_img = await page.evaluate(()=> {
    const img = document.querySelector(".product.media").children[1].src;
    return img;
})

console.log(price);
console.log(product_img);

return { price, product_img };

};

getPrice();

// getPrice().then(infos => {
//   let prod_img = document.createElement('img');
//   let prod_price = document.createElement('h1');

//   prod_price.innerText = infos.price;
//   prod_img.src = infos.product_img;

//   document.body.appendChild(prod_price);
//   document.body.appendChild(prod_img);
// });