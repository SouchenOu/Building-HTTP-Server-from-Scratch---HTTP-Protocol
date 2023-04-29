//import Typewriter from 'typewriter-effect/dist/core';
const txtAnim = document.querySelector('h1');
new Typewriter(txtAnim, {
        deleteSpeed: 20
    })
    .changeDelay(20)
    .typeString('Hi my name is Ouchen soukaina')
    .pauseFor(6000)
    .typeString('<strong>, Dev Front-end</strong>')
    .pauseFor(6000)
    .deleteChars(13)
    .typeString('<span style="color: #3D3635"> I know a little bit of some things </span> !')
    .pauseFor(6000)
    .deleteChars(40)
    .typeString('<strong style="color: #8A4117">, L\'ets see some of my works </strong> !')
    .pauseFor(6000)
    .deleteChars(30)
    .typeString('<strong style="color:#7A5DC7"> WELCOME FRINDS! </strong>')
    .start()