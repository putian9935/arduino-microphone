#ifndef SERVER_RESPONSES_HPP
#define SERVER_RESPONSES_HPP


char const page[] = R"(HTTP/1.1 200 OK
Connection: Keep-Alive
Content-Type: text/html

<!DOCTYPE HTML>
<html> 
<head>
<title>Arduino online microphone</title>
<link rel="icon" href="data:;base64,iVBORw0KGgo=">
<style>
    .bg {height:100vh; overflow-y: hidden;  
  background-position: center;
  background-repeat: no-repeat;
  background-size: cover;
  position: relative;
  background: linear-gradient(-45deg, #ee7752, #e73c7e, #23a6d5, #23d5ab);
	background-size: 400% 400%;
	animation: gradient 15s ease infinite;}
  @keyframes gradient { 0% { background-position: 0% 50%; }
	50% { background-position: 100% 50%; }
	100% { background-position: 0% 50%; }
   }
    body {text-align: center; color: white;}
    .header {margin: 10vh 10vw 0vh 10vw; padding: 10vh; background: rgba(255, 209, 216, 0.2); border-radius: 5vw;}
    .container {padding: 5vh 5vh;}
    .circle {position: relative; height: 15vw; width: 15vw; background-color: #fffa; border-radius: 50%; display: inline-block;}
    .rec {position: absolute; top: 3.5vw; left:3.5vw; width: 8vw;height: 8vw;background: #f00a; border-radius: 0.5vw;}
    .circle:hover {box-shadow: 0vw 0vw 1vw  #fffa; cursor: pointer;}
</style>
</head>
<body class="bg">
<div class="header">
<h1>Arduino online microphone</h1>
<p>Press the button below to save a 10-second recording.</p>
</div>
<div class="container">
<div class="circle" onclick="location.href='./1';"><div class="rec"></div></div>
</div>
<footer>&copy;Li Putian, 2022</footer>
</body>
</html>)";


char const audio_header[] = R"(HTTP/1.1 200 OK
Content-Type: audio/x-wav
Content-Disposition: attachment; filename="1.wav"

)";

#define WAV_FORMAT_HEADER_SIZE 44

uint8_t const wav_format_header[] = {
      82, 73, 70, 70, 255, 255, 255, 255, 87,  65,  86,  69,  102, 109, 116,
      32, 16, 0,  0,  0,   1,   0,   1,   0,   128, 62,  0,   0,   0,   125,
      0,  0,  2,  0,  16,  0,   100, 97,  116, 97,  255, 255, 255, 255,
  };

#endif 