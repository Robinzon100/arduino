const express = require('express');
const app = express();
const bodyParser = require('body-parser')
const path = require('path')
const fs = require('fs')

const PORT = 3000

require('dotenv').config()


app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.use(express.static(path.join(__dirname, '/public')));

app.set("view engine", "ejs");
app.set("views", "views");

app.use(function (req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    next();
});

app.get('/', (req, res) => {
    res.render("index.ejs", {
        domainName: process.env.DOMAIN_NAME
    });
});



app.get('/state', (req, res) => {
    let sendState

    fs.readFile("state.txt", 'utf8', (err, data) => {
        console.log("state content " + data)
        sendState = data;

        res.json({
            state: sendState
        });
    })
});


app.post('/state', (req, res) => {
    const { state } = req.body;
    let sendState

    fs.writeFileSync('state.txt', state, 'utf8', _ => {
        console.log("whitten in file " + state);
    });

    fs.readFile("state.txt", 'utf8', (err, data) => {
        console.log("state content " + data)
        sendState = data;

        res.json({
            state: sendState
        });
    })
});







app.listen(PORT, () => {
    console.log("running on port " + PORT)
});