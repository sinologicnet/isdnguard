<h1>Asterisk module for ISDNGuard</h1>

<h2>Description</h2>
This project is intended to serve as general support for maintaining res_isdnguard module.
A generator of watchdog signal connected to serial port to enable failover system ports from Junghanns ISDNGuard.<br />

<div style="text-align: center;"><img src="http://www.junghanns.net/images/ISDNguard.jpg" alt="failover junghanns"/></div>

<h2>Why this module</h2>
Junghanns stopped supporting failover ISDNGuard for their devices in Asterisk 1.6 and later, 
so we did a module from scrach compatible with Asterisk 1.8, Asterisk 10, 11 and 12 and we publish it here 
so that the community can continue its development if they desired.

<h2>Installation</h2>
<pre>
    cd /usr/src/asterisk-xxx
    git clone https://github.com/sinologicnet/isdnguard
    cp isdnguard/res_isdnguard.c res/
    make
    make install
    ls -la res_isdnguard.so
</pre>


<h2>Author</h2>
Elio Rojano
http://www.sinologic.net/
