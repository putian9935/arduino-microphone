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
</head>
<body>
<h1>Arduino online microphone</h1>
<main>
<p>Press the link below to start a 10-second recording.</p>
<p><a href="1">Start</a></p>
</main>
<footer>&copy;Li Putian, 2022</footer>
</body>
</html>)";


char const audio_header[] = R"(HTTP/1.1 200 OK
Content-Type: audio/x-wav
Content-Disposition: attachment; filename="1.wav"

)";

#endif 