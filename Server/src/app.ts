require("dotenv").config();
import express, { Application } from "express";
import cors from "cors";
import path from "path";
import apiRouter from "./api/index";
import { getIndexForm } from "./controllers/database";
import errLogEvents from "./middleware/errorHandle";
import { modelurl } from "./controllers/model";

const port = process.env.PORT || 10000;

//shuts down if crucial envs are not given
if (port == undefined || modelurl == undefined) {
  console.log("process-exit Env issues");
  process.exit(-1);
}

const app: Application = express();

app.use(cors());
app.set("view engine", "ejs");
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(express.static(path.join(__dirname, "public")));

app.get("/", async (_req, res) => {
  const cardlist = await getIndexForm("66b393083821775e2b731015");
  res.render(path.join(__dirname, "./views/index"), {
    scriptLabel: "index",
    cards: cardlist,
  });
});

//home redirects
app.get("/index*", (req, res) => {
  res.redirect("/");
});

app.get("/service", (_req, res) => {
  res.render(path.join(__dirname, "./views/service"), {
    scriptLabel: "service",
  });
});

app.get("/about", (_req, res) => {
  res.render(path.join(__dirname, "./views/about"), {
    scriptLabel: "about",
  });
});

app.use("/api", apiRouter);

//404s
app.all("*", (_req, res) => {
  res.render(path.join(__dirname, "./views/404"), {
    scriptLabel: "404",
  });
});

//error logs
app.use(errLogEvents);

app.listen(port, () => {
  console.log(`Senml(). listening at http://localhost:${port}`);
});
