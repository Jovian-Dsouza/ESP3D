/*
  syncwebserver.h - ESP3D sync functions file

  Copyright (c) 2014 Luc Lebosse. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef SYNCWEBSERVER_H
#define SYNCWEBSERVER_H
#include "config.h"
#define NODEBUG_WEBSOCKETS
#include <WebSocketsServer.h>

extern void handle_web_interface_root();
extern void handle_login();
extern void handleFileList();
extern void SPIFFSFileupload();
extern void handle_not_found();
extern void handle_web_command();
extern void handle_web_command_silent();
extern void handle_serial_SDFileList();
extern void SDFile_serial_upload();
extern WebSocketsServer * socket_server;
extern void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

////////////////////////////////////////////////////////////////
extern void handleIndex();
extern void handleFileUpload();
extern void handlePrint();
extern void handlePercent();
extern void printloop();
extern void handleRedirectSD();
extern void loadSDcard();

//void lcd(String string);
void Stop();
void countLines();
void PrintLoop();

const char SDcard_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<div id="demo">
<h1>Wireless Print</h1>
  <form enctype="multipart/form-data" action="/SDcard/fileUpload" method="POST">
    <input type="hidden" name="MAX_FILE_SIZE" value="100000">
    Choose a file to upload: <input name="file" type="file"><br>
    <input type="submit" value="Upload">
  </form>
  
  <button type="button" onclick="sendData(0)">Print</button>
  <button type="button" onclick="sendData(1)">Pause</button>
  <button type="button" onclick="sendData(2)">Resume</button>
  <button type="button" onclick="sendData(3)">Stop</button><br>
    
</div>

<div>
  Print % : <span id="printPercent">0</span><br>
  Print Status : <span id="printState">NA</span>
</div>
<script>
function sendData(printStatus) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("printState").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "SDcard/print?state="+printStatus, true);
  xhttp.send();
}

setInterval(function() {
  // Call a function repetatively with 2 Second interval
   getData();
}, 2000); //2000mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("printPercent").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "SDcard/readPercent", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
////////////////////////////////////////////////////////////////

#ifdef SSDP_FEATURE
extern void handle_SSDP ();
#endif

#ifdef WEB_UPDATE_FEATURE
extern void handleUpdate ();
extern void WebUpdateUpload ();
#endif

#endif
