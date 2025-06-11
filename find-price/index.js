import puppeteer from "puppeteer"

const getPrice = async()=> {

// start puppeteer
const browser = await puppeteer.launch({
	headless: true, defaultViewport: null
});

// open new browser page
const page = await browser.newPage();

// get the page
let url = "https://puregold.com.ph/pgcatalog/category/subcategory/category/SNACKS/subcat/CHIPS,%20NUTS%20&%20CORN";
await page.goto(url, {
	waitUntil: "domcontentloaded"
});


const product_name = await page.evaluate(()=> {
    const p_name = document.querySelector(".ImageContainer").children[0].innerHTML;
    return p_name;
})

const images = await page.evaluate(()=> {
    const image = document.querySelector(".ImageContainer").children[0].src;
    return image;
})

const prices = await page.evaluate(()=> {
    const price = document.querySelector(".product-price-style").innerHTML;
    return price;
})

console.log(images);
console.log(prices);

// return { price, product_img };

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