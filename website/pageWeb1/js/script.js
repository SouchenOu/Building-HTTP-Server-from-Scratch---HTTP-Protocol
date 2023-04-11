let searchForm = document.querySelector('.search-form');

document.querySelector('#search-btn').onclick = () => {
    searchForm.classList.toggle('active');
    ShoppingCart.classList.remove('active');
    LoginCart.classList.remove('active');
    navbar.classList.remove('active');
}

let ShoppingCart = document.querySelector('.shopping-cart');

document.querySelector('#cart-btn').onclick = () => {
    ShoppingCart.classList.toggle('active');
    LoginCart.classList.remove('active');
    navbar.classList.remove('active');
    searchForm.classList.remove('active');
}
let LoginCart = document.querySelector('.login-form');

document.querySelector('#login-btn').onclick = () => {
    LoginCart.classList.toggle('active');
    navbar.classList.remove('active');
    searchForm.classList.remove('active');
    ShoppingCart.classList.remove('active');
}
let navbar = document.querySelector('.nav-bar');

document.querySelector('#menu-btn').onclick = () => {
    navbar.classList.toggle('active');
    searchForm.classList.remove('active');
    ShoppingCart.classList.remove('active');
    LoginCart.classist.remove('active');
}
window.onscroll = () => {
    searchForm.classList.remove('active');
    navbar.classList.remove('active');
    ShoppingCart.classList.remove('active');
    LoginCart.classist.remove('active');
}

const txtAnim = document.querySelector('h1');
new Typewriter(txtAnim, {
        deleteSpeed: 20
    })
    .changeDelay(20)
    .typeString('<span style="color :#3D3635">Welcome</span>')
    .pauseFor(3000)
    .deleteChars(20)
    .changeDelay(20)
    .typeString('<span style="color :#3D3635">to so-shop</span>')
    .pauseFor(3000)
    .deleteChars(20)
    .start()