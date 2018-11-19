<!--
Generic Error Handler & Malicious Spider Blocker v1.4 -- iERROR Edition
Copyright � 1998-2005 adminware, llc
http://www.adminware.com/
-->

<iREM -- Malicious Spider Blocker -- >
<iIF EXPR='NOT <iSTRCMP SRC=":i_browser" DST=""> AND (<iSTRICMP SRC="Java/1." DST=`<iSTRLEFT SRC=":i_browser" NUM="7">`> or <iSTRIN SRC="ExtractorPro,Sqworm,MuscatFerret,webtop.com,NICErsPRO,WebWeasel,EmailCollector,CherryPicker,Cherry Picker,EirGrabber,EmailSiphon,EmailWolf,Sonic Email Collector,EmailSiphon,Top10ContactBot,AnzwersCrawl,EchO!,zzZ,Exploiter,WebStripper,Hunt,LinkWalker,htdig/3.1.5 (kkinder@tridog.com),UniFind Site Spider; email spider@unifind.com,XH p(�$pp�G,Scooter-W3-1.0" DST=":i_browser" CASE=FALSE>)' ALIAS="isMS">
	<iFILE NAME="spamspider.log" DATA=`<iDATETIME>|:i_ip|<iIP ADDRESS=:i_ip>|:i_browser|:i_http_HTTP_REFERER|:i_path:i$crlf` OP=APPEND>
	<iREDIR URL="http://disney.go.com/">
</iIF ALIAS="isMS">

<iERROR>

<iREM -- Remove Database DSN, Username & Password -->
<iREPLACE VAR="i_errordetail" SRC="`" DST="">
<iREGEXREPLACE SRC=`:i_errordetail` REGEX=`DBNAME=".*?"` NEWTEXT=`DBNAME="[ removed ]"` OUTVAR="i_errordetail">
<iREGEXREPLACE SRC=`:i_errordetail` REGEX=`LOGIN=".*?"` NEWTEXT=`LOGIN="[ removed ]"` OUTVAR="i_errordetail">

<iREM -- Global Configuration -- >
<iDEFAULT NAME="showErrors" VALUE="0">						<iREM -- Show errors to the end-user (1) or show a generic message (0)? -- >
<iDEFAULT NAME="doNotify" VALUE="1">						<iREM -- Notify admin/support via email of error occurring -- >
<iDEFAULT NAME="notifyTo" VALUE="webmaster@:i_hostname">		<iREM -- Default to address for notifications -- >
<iDEFAULT NAME="notifyFrom" VALUE="errorhandler@:i_hostname">	<iREM -- Default from address for notifications -- >
<iDEFAULT NAME="dbMode" VALUE=" (unknown)">					<iREM -- Default database mode -- >
<iDEFAULT NAME="errPrg" VALUE=":i_hostname:i_script_name">		<iREM -- Default program name -- >
<iDEFAULT NAME="isAdmin" VALUE="0">						<iREM -- Is admin seeing this?  Override yourself, however you'd like... -- >
<iDEFAULT NAME="adminName" VALUE="Admin">					<iREM -- Administrator's username (username/ck_usr/i_auth_user) -- >
<iDEFAULT NAME="debugIP" VALUE="24.1.102.150">				<iREM -- Debugging IP -- >

<iIF EXPR='<iSTRIN SRC=":username" DST=":adminName"> OR <iSTRIN SRC=":ck_usr" DST=":adminName"> OR <iSTRIN SRC=":i_auth_user" DST=":adminName"> OR <iSTRCMP SRC=":i_ip" DST=":debugIP"> OR :isAdmin' ALIAS="isAdministrator">
	<iSET isAdmin = 1 showErrors = 1 doNotify = 0>
</iIF ALIAS="isAdministrator">

<iHEAPDUMP OUTVAR="dump">
<iREPLACE VAR="dump" SRC="<br>" DST=":i$crlf" OUTVAR="mailDump">
<iREPLACE VAR="dump" SRC="<br>" DST="<br />">
<iREPLACE VAR="i_errordetail" SRC="<br>" DST=":i$crlf" OUTVAR="mailDetail">
<iREPLACE VAR="i_errordetail" SRC="<br>" DST="<br />">
<iIF COND=<iSTRIN SRC=":i_errordetail" DST="i_errordetail" CASE=FALSE> ALIAS="noDetail"><iSET i_errordetail = ""></iIF ALIAS="noDetail">
<iDATETIME FMT="%m-%d-%Y @ %H:%M:%S" OUTVAR="dateTime">
<iREPLACE VAR="notifyFrom" SRC="@www." DST="@">
<iREPLACE VAR="notifyTo" SRC="@www." DST="@">
<iIP ADDRESS=":i_ip" OUTVAR="clientHostName">

<iSET isSQLError = "">
<iIF COND=<iSTRICMP SRC=":i_error" DST="350"> ALIAS="sqlError"><iSET isSQLError = ":i$crlf<b>SQL Error:</b>         :i_sqlerrortext:i$crlf<b>SQL Statement:</b>     :i_sqlerrorstmt"></iIF ALIAS="sqlError">

<iSET lastInclude = "">
<iIF COND=<iISDEF VAR="i_priv_included"> ALIAS="inc"><iSET lastInclude = ":i$crlf<b>Last Include:</b>      :i_priv_included"></iIF ALIAS="inc">

</td></td></td></th></th></th></tr></tr></tr></table></table></table></a></abbrev></acronym></address></applet></au></b></banner></big></blink></blockquote></bq></caption></center></cite></code></comment></del></dfn></dir></div></div></dl></em></fig></fn></font></form></frame></frameset></h1></h2></h3></h4></h5></h6></head></i></ins></kbd></listing></map></marquee></menu></multicol></nobr></noframes></noscript></note></ol></p></param></person></plaintext></pre></q></s></samp></script></select></small></strike></strong></sub></sup></table></td></textarea></th></title></tr></tt></u></ul></var></wbr></xmp>

	<style type="text/css"><!--
	body.err, p.err {
		background-color: #ffffff;
		color : #000000;
		font : normal normal 13px/14px Verdana, Arial, Helvetica, sans-serif;
	}
	h1.err {
		font : normal bold 14px/15px Verdana, Arial, Helvetica, sans-serif;
	}
	pre.err {
		font : normal normal 13px/14px "Courier New", Courier, monospace;
	}
	span.err {
		color : #FF0000;
		font-weight : bold;
	}
	blockquote.err {
		color : #FF0000;
		font-weight : bold;
	}
	//--></style>

<pre><hr noshade />
<h1 class="err">Generic Error Handler & Malicious Spider Blocker v1.4 -- iERROR Edition</h1>

<p class="err">An error has occurred in <span class="err">:errPrg</span>:</p>

<pre class="err"><iIF COND=<iSTRICMP SRC=":showErrors" DST="1"> ALIAS="show">
<b>Date & Time:</b>       :dateTime
<b>Error Code:</b>        :i_error
<b>Error Text:</b>        :i_errortext
<b>OS Error</b>           :i_os_error
<b>Error Hint:</b>        :i_hinttext
<b>Error Details:</b>
<blockquote class="err">:i_errordetail</blockquote>:isSQLError
<b>Page:</b>              :i_path
<b>Query String:</b>      :i_query_string:lastInclude
<b>Cookies:</b>           :i_http_http_cookie
<b>Cookie Path:</b>       :i_cookie_path
<b>Hostname:</b>          :i_hostname
<b>Path/Filename:</b>     :i_path
<b>Browser:</b>           :i_browser
<b>Client IP:</b>         :i_ip
<b>Client Hostname:</b>   :clientHostName
<b>Auth'd User:</b>       :i_auth_user
<b>Referer:</b>           :i_referer
</iIF ALIAS="show"><iIF EXPR='<iSTRICMP SRC=":isAdmin" DST="1"> OR <iSTRICMP SRC=":showErrors" DST="1">' ALIAS="show"><hr noshade />:dump<iELSE ALIAS="show">:i$crlf<span class="err">An administrator has been notified. &nbsp;We apologize for the inconvenience.</span>:i$crlf:i$crlf<iREM>Click <a href=":i_referrer">here</a> to go back to the previous page.</iIF ALIAS="show">
</pre>

<iIF COND=<iSTRICMP SRC=":doNotify" DST="1"> ALIAS="notify">
	<iMAIL ADDRESS=":notifyTo" FROM=":notifyFrom" SUBJECT="ERROR: :errPrg:dbMode" EHANDLE="QUIET">Generic Error Handler & Malicious Spider Blocker v1.4 -- iERROR Edition

An error has occurred in :errPrg:

Date & Time   = :dateTime
Error Number  = :i_error
Error Message = :i_errortext
OS Error      = :i_os_error
Error Hint    = :i_hinttext
Error Details =

:mailDetail:isSQLError
Page:             :i_path
Query String:     :i_query_string:lastInclude
Cookies:          :i_http_http_cookie
Cookie Path:      :i_cookie_path
Hostname:         :i_hostname
Path/Filename:    :i_path
Browser:          :i_browser
Client IP:        :i_ip
Client Hostname:  :clientHostName
Auth'd User:      :i_auth_user
Referer:          :i_referer

:mailDump
</iMAIL>
</iIF ALIAS="notify">

</iERROR>
