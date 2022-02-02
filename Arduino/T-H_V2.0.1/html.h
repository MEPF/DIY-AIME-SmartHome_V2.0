/****************************************************************************************************************/
/*  HTML MAIN - Notification                                                                                           */
/****************************************************************************************************************/

String htmlTH(float temperatureStat, float humidityStat, String deviceName){
String ptr = "<!DOCTYPE html>\n";
ptr +="<html lang=\"en\">\n";
ptr +="<head>\n";
ptr +="<meta http-equiv=\"refresh\" content=\"30\">\n";
ptr +="<meta charset=\"utf-8\">\n";
ptr +="<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
ptr +="<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
ptr +="<link rel=\"icon\" href=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADIAAAAyCAYAAAAeP4ixAAAEZklEQVRoge2Ze4jVRRTHP9vabuG6iFZCZasRPQmDshKLIopKyMKotiJaLCP6o6eVvbaEkEIiLYwebNFLCxEjTIoge9o/ZS97uav2IMvdanOlcnPtxsTnyjD99t67tfdG8fvCj9/MOec3M2fmnJkz50eOHDly5Pi/4kugD2iupn67VLHt/YFfgS+AV4AtwDFV7K8qmAYUgOVR4w9Iu+y/osQNDvj2DN6l8hZm8ILpTQD2iZ79gD1qMOa/YLEDPauEzGRlXk/oM4BtwED0/AZcXcPx/4m1DvDgCmT3BH4AvgfGSNsd+MA2is9mYFSVx70TE3XqLqAxooeNZLeoHsp1ybdvOODJ1l9IFFlbIx043Q5XZPDC4OYAI4BdgdnAmRlyi2yjFXgsUeTTGuiw06nvyOCNUYklwN3AfOBxd669MuRnJgrUTJGnyzh1sP+tQK/vYrlPMxyb8c0kfaImigQbf89ODkt49cApwLXyJzn743xCeTyww1WalvhUQHPkN0PykaGc7MGp+4Emd5iPM9qaAhwA/CS/21nebPlry0GhEzMUCSt2PPCI9aYhjK8iFJ36uTLC4fC6zXBkXAY/OH0PcC8wskxb7fY5c7iUKOXUKZodQN8gijSoyIIKreGCEpHAkFDJSV1EmO2b7bRX88vCJuAJYF6Fh90Ux/BaKaERg9DDbH0EHAocAnxWQYe/6wOjXZlgZt9Fh2DBFQm87cB6Q5FyeNuN4nNX80Anqiwm2lFXcjIPBTvs7Fs777HcrUJZ228leNPvj04Z9Um9DVgFPA9MrXDGsvCMqxom5ENnPyjRCZzvZevv4FF97yHgZ2D1YG2sc0cZDhwF3Ko5NbppzBimtsNZ9c0wtVUWjcldYuw/MNUcOXLkyJGjqkhDlCM9fcNzmje+kQaNITS4BbgQ+AXY4Detyp1twiEEij9GbV4CXGm40xnRW01INBnGxAiXq5sMazZFjMMdQ52x4KBYFF0zB4xoQ5jR4h2jYIwT3h02MmB9e/TtdHlLrG/1fb305da3+H4yGtBCaeGWeXJEvy7qv63c6t6vcIoVCf0+I9p6B/luxNto9NvgNwukd1of5ftO6c9GbU+3fEbS/3HSK8463uUHIZVzBXC59POkvwqcGsnXSY+j0HekBSWXAmuAizW5e1RwdCT/vpmVgJdd2ZfMQl4jvcM2X/R6ML+cIu2RmfSbiy0GflMj8wr+MUH6euV7lA/8G+Wdk6R30nTqPOnHWu/U/9ojKxhvPiyY+dwoq39RKUWK9pnep09wJonyT/3O+ic691N2cpJyLbbVHs12fL+5Sv65Ea1guimut3m/6U/oK0sp8qBCYffaG9jXXWuN9IOUWxVdXQsZqSHcYQrOegjf34p8ofh74WEnrbi6K6W3ROYc8mezLIdr7hGW55ZSZI7m0x3lomZrXhuc+S5np7gD9ZpUy0KH5rbOXwSzlNmmXwTf+spLUvjD1WD7Gx3HsqjN1cr1eOXN7zY5cuTI8S8D+AMzjVFfbeP2NgAAAABJRU5ErkJggg==\" sizes=\"16x16 32x32\" type=\"image/png\">\n";
ptr +="<title>T & H > AIME - Smart Home</title>\n";
ptr +="<style>\n";
ptr +="* {box-sizing: border-box;}\n";
ptr +="html {font-family: sans-serif;}\n";
ptr +="body {\n";
ptr +="background: #f3e0e2;\n";
ptr +="display: flex;\n";
ptr +="justify-content: center;\n";
ptr +="align-items: center;\n";
ptr +="flex-direction: column;\n";
ptr +="}\n";
ptr +="h1 {font-weight: bold;margin: 0;}\n";
ptr +="h2 {font-weight: bold;margin: 0;}\n";
ptr +="h3 {font-weight: bold; margin: 0; font-size: 14px;}\n";
ptr +="span {font-size: 10px;}\n";
ptr +="button {\n";
ptr +="border-radius: 20px;\n";
ptr +="border: 1px solid #0ea0ff;\n";
ptr +="background-color: #009530;\n";
ptr +="box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19);\n";
ptr +="color: #FFFFFF;\n";
ptr +="font-size: 12px;\n";
ptr +="font-weight: bold;\n";
ptr +="padding: 12px 35px;\n";
ptr +="letter-spacing: 1px;\n";
ptr +="text-transform: uppercase;\n";
ptr +="transition: transform 80ms ease-in;\n";
ptr +="max-width: 120px;\n";
ptr +="}\n";
ptr +="button:hover {\n";
ptr +="background-color: #fff;\n";
ptr +="border-color: #189cf0;\n";
ptr +="color: #189cf0;\n";
ptr +="}\n";
ptr +="nav {\n";
ptr +="position: fixed;\n";
ptr +="padding: 5px 5px;\n";
ptr +="border-bottom: 2px solid #ddd;\n";
ptr +="height: 60px;\n";
ptr +="top: 0;\n";
ptr +="width: 100%;\n";
ptr +="background: linear-gradient(120deg,#009530,#0ea0ff);\n";
ptr +="}\n";
ptr +=".logo {width: 100px;}\n";
ptr +=".label {\n";
ptr +="position: fixed;\n";
ptr +=" padding-top: 15px;\n";
ptr +="font-size: 1.2rem;\n";
ptr +="padding-left: 10px;\n";
ptr +="color: #ffffff;\n";
ptr +="}\n";
ptr +="label {\n";
ptr +="display: inline-block;\n";
ptr +="font-size: 12px;\n";
ptr +="color: #000000;\n";
ptr +="text-align: left;\n";
ptr +="}\n";
ptr +=".menu {\n";
ptr +="position: fixed;\n";
ptr +="top: 8px;\n";
ptr +="font-size: 1.3rem;\n";
ptr +="right: 20px;\n";
ptr +="}\n";
ptr +="form {\n";
ptr +="background-color: #FFFFFF;\n";
ptr +="display: flex;\n";
ptr +="justify-content: center;\n";
ptr +="flex-direction: column;\n";
ptr +="text-align: center;\n";
ptr +="position: fixed;\n";
ptr +="top: 50%;\n";
ptr +="left: 50%;\n";
ptr +="transform: translate(-50%, -50%);\n";
ptr +="}\n";
ptr +=".container {\n";
ptr +="background-color: #fff;\n";
ptr +="border-radius: 5px;\n";
ptr +="box-shadow: 0 14px 28px rgba(0,0,0,0.25), 0 10px 10px rgba(0,0,0,0.22);\n";
ptr +="position: relative;\n";
ptr +="overflow: hidden;\n";
ptr +="width: 320px;\n";
ptr +="max-width: 100%;\n";
ptr +="min-height: 400px;\n";
ptr +="position: fixed;\n";
ptr +="top: 50%;\n";
ptr +="left: 50%;\n";
ptr +="transform: translate(-50%, -50%);\n";
ptr +="}\n";
ptr +=".form-container {\n";
ptr +="display: flex;\n";
ptr +="align-items: center;\n";
ptr +="justify-content: center;\n";
ptr +="height: 100%;\n";
ptr +="}\n";
ptr +="img {\n";
ptr +="width: 80%;\n";
ptr +="}\n";
ptr +="footer {\n";
ptr +="position: fixed;\n";
ptr +="padding-top: 10px;\n";
ptr +="border-top: 2px solid #ddd;\n";
ptr +="height: 60px; bottom: 0;\n";
ptr +="width: 100%;\n";
ptr +="background: linear-gradient(120deg,#009530,#0ea0ff);\n";
ptr +="text-align: center;\n";
ptr +="}\n";
ptr +=".footer_text {font-size: 16px; color: #ffffff;}\n";
ptr +="@media only screen and (max-width: 600px) {\n";
ptr +=".logo {padding-top: 10px;width: 60px;}\n";
ptr +=".label {padding-top: 15px; font-size: 1.0rem;}\n";
ptr +=".menu {top: 10px; font-size: 1.0rem; right: 10px;}\n";
ptr +="button {font-size: 8px;padding: 14px 14px;}\n";
ptr +="}\n";
ptr +="</style>\n";
ptr +="</head>\n";
ptr +="<body>\n";
ptr +="<nav>\n";
ptr +="<img class=\"logo\" alt=\"AIME - Smart Home\" src=\"data:image/png;base64,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\">\n";
ptr +="<label class=\"label\">AIME - Smart Home</label>\n";
ptr +="</nav>\n";
ptr +="<div class=\"container\">\n";
ptr +="<div class=\"form-container\">\n";
        ptr +="<form action=\"/\" method=\"POST\">\n";
            ptr +="<h2>\n"; ptr +=deviceName; ptr +="</h2>\n";
          ptr +="<br>\n";
          ptr +="<br>\n";
          ptr +="<br>\n";
            ptr +="<h2>TEMPERATURE</h2>\n";
          ptr +="<br>\n";
          
            ptr +="<h1 class=\"temperature\">\n";
            ptr +=(int)temperatureStat; 
            ptr +="&#8451;</h1>\n";
            
          ptr +="<br>\n";
          ptr +="<br>\n";
          ptr +="<h2>HUMIDITY</h2>\n";
          ptr +="<br>\n";
          
            ptr +="<h1 class=\"humidity\">\n";
            ptr +=(int)humidityStat;
            ptr +="&#37;</h1>\n";
            
          ptr +="<br>\n";
        ptr +="</form>\n";
ptr +="</div>\n";
ptr +="</div>\n";
ptr +="<footer>\n";
ptr +="<label class=\"footer_text\">\n";
ptr +="&copy; 2020<script>new Date().getFullYear()>2010&&document.write(\"-\"+new Date().getFullYear());</script> DIY - Smart Home\n";
ptr +="</label>\n";
ptr +="</footer>\n";
ptr +="</body>\n";
ptr +="</html>\n";
return ptr;
}


/****************************************************************************************************************/
/*  HTML 404 - NotFound                                                                                         */
/****************************************************************************************************************/

const char html404[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADIAAAAyCAYAAAAeP4ixAAAEZklEQVRoge2Ze4jVRRTHP9vabuG6iFZCZasRPQmDshKLIopKyMKotiJaLCP6o6eVvbaEkEIiLYwebNFLCxEjTIoge9o/ZS97uav2IMvdanOlcnPtxsTnyjD99t67tfdG8fvCj9/MOec3M2fmnJkz50eOHDly5Pi/4kugD2iupn67VLHt/YFfgS+AV4AtwDFV7K8qmAYUgOVR4w9Iu+y/osQNDvj2DN6l8hZm8ILpTQD2iZ79gD1qMOa/YLEDPauEzGRlXk/oM4BtwED0/AZcXcPx/4m1DvDgCmT3BH4AvgfGSNsd+MA2is9mYFSVx70TE3XqLqAxooeNZLeoHsp1ybdvOODJ1l9IFFlbIx043Q5XZPDC4OYAI4BdgdnAmRlyi2yjFXgsUeTTGuiw06nvyOCNUYklwN3AfOBxd669MuRnJgrUTJGnyzh1sP+tQK/vYrlPMxyb8c0kfaImigQbf89ODkt49cApwLXyJzn743xCeTyww1WalvhUQHPkN0PykaGc7MGp+4Emd5iPM9qaAhwA/CS/21nebPlry0GhEzMUCSt2PPCI9aYhjK8iFJ36uTLC4fC6zXBkXAY/OH0PcC8wskxb7fY5c7iUKOXUKZodQN8gijSoyIIKreGCEpHAkFDJSV1EmO2b7bRX88vCJuAJYF6Fh90Ux/BaKaERg9DDbH0EHAocAnxWQYe/6wOjXZlgZt9Fh2DBFQm87cB6Q5FyeNuN4nNX80Anqiwm2lFXcjIPBTvs7Fs777HcrUJZ228leNPvj04Z9Um9DVgFPA9MrXDGsvCMqxom5ENnPyjRCZzvZevv4FF97yHgZ2D1YG2sc0cZDhwF3Ko5NbppzBimtsNZ9c0wtVUWjcldYuw/MNUcOXLkyJGjqkhDlCM9fcNzmje+kQaNITS4BbgQ+AXY4Detyp1twiEEij9GbV4CXGm40xnRW01INBnGxAiXq5sMazZFjMMdQ52x4KBYFF0zB4xoQ5jR4h2jYIwT3h02MmB9e/TtdHlLrG/1fb305da3+H4yGtBCaeGWeXJEvy7qv63c6t6vcIoVCf0+I9p6B/luxNto9NvgNwukd1of5ftO6c9GbU+3fEbS/3HSK8463uUHIZVzBXC59POkvwqcGsnXSY+j0HekBSWXAmuAizW5e1RwdCT/vpmVgJdd2ZfMQl4jvcM2X/R6ML+cIu2RmfSbiy0GflMj8wr+MUH6euV7lA/8G+Wdk6R30nTqPOnHWu/U/9ojKxhvPiyY+dwoq39RKUWK9pnep09wJonyT/3O+ic691N2cpJyLbbVHs12fL+5Sv65Ea1guimut3m/6U/oK0sp8qBCYffaG9jXXWuN9IOUWxVdXQsZqSHcYQrOegjf34p8ofh74WEnrbi6K6W3ROYc8mezLIdr7hGW55ZSZI7m0x3lomZrXhuc+S5np7gD9ZpUy0KH5rbOXwSzlNmmXwTf+spLUvjD1WD7Gx3HsqjN1cr1eOXN7zY5cuTI8S8D+AMzjVFfbeP2NgAAAABJRU5ErkJggg==" sizes="16x16 32x32" type="image/png">
    <title>404 > AIME - SmartHome</title>
    <style>
      * {
      -webkit-box-sizing: border-box;
      box-sizing: border-box;
      }
      body {padding: 0;margin: 0;}
      #notfound {
      position: relative;
      height: 100vh;
      }
      #notfound .notfound {
      position: absolute;
      left: 50%;
      top: 50%;
      -webkit-transform: translate(-50%, -50%);
      -ms-transform: translate(-50%, -50%);
      transform: translate(-50%, -50%);
      }
      .notfound {
      max-width: 920px;
      width: 100%;
      line-height: 1.4;
      text-align: center;
      padding-left: 15px;
      padding-right: 15px;
      }
      .notfound .notfound-404 {
      position: absolute;
      height: 100px;
      top: 0;
      left: 50%;
      -webkit-transform: translateX(-50%);
      -ms-transform: translateX(-50%);
      transform: translateX(-50%);
      z-index: -1;
      }
      .notfound .notfound-404 h1 {
      font-family: 'Maven Pro', sans-serif;
      color: #ececec;
      font-weight: 900;
      font-size: 276px;
      margin: 0px;
      position: absolute;
      left: 50%;
      top: 50%;
      -webkit-transform: translate(-50%, -50%);
      -ms-transform: translate(-50%, -50%);
      transform: translate(-50%, -50%);
      }
      .notfound h2 {
      font-family: 'Maven Pro', sans-serif;
      font-size: 46px;
      color: #000;
      font-weight: 900;
      text-transform: uppercase;
      margin: 0px;
      }
      .notfound p {
      font-family: 'Maven Pro', sans-serif;
      font-size: 16px;
      color: #000;
      font-weight: 400;
      text-transform: uppercase;
      margin-top: 15px;
      }
      .notfound a {
      font-family: 'Maven Pro', sans-serif;
      font-size: 14px;
      text-decoration: none;
      text-transform: uppercase;
      background: #189cf0;
      display: inline-block;
      padding: 16px 38px;
      border: 2px solid transparent;
      border-radius: 40px;
      color: #fff;
      font-weight: 400;
      -webkit-transition: 0.2s all;
      transition: 0.2s all;
      }
      .notfound a:hover {
      background-color: #fff;
      border-color: #189cf0;
      color: #189cf0;
      }
      @media only screen and (max-width: 480px) {
      .notfound .notfound-404 h1 {
      font-size: 142px;
      }
      .notfound h2 {
      font-size: 26px;
      }
      }
    </style>
  </head>
  <body>
    <div id="notfound">
      <div class="notfound">
        <div class="notfound-404">
          <h1>404</h1>
        </div>
        <h2>Page not found!</h2>
        <p>The page you are looking is unavailable.</p>
        <br>
        <a onclick="location.href='/'">Back To Homepage</a>
      </div>
    </div>
  </body>
</html>
)=====";
