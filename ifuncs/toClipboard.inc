<!iHTML>

<iREM -- Prepare Text for Clipboard Copy -- >
<iDEFAULT NAME="jsTextOut" VALUE="">
<iREPLACE VAR="jsTextOut" SRC=":i$crlf" DST="\n">
<iREPLACE VAR="jsTextOut" SRC=`"` DST=`\"`>

<iREM -- Show Clipboard Copy Option if Browser Supported -- >
<SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript"><!--
function toClipboard(textToCopy) {
	document.getElementById(textToCopy).style.visibility = "visible";
	document.getElementById(textToCopy).select();
	var success = document.execCommand("Copy");
	document.getElementById(textToCopy).style.visibility = "hidden";
}
if(document.queryCommandSupported("Copy")) {
	document.writeln("<A HREF=\"javascript:toClipboard('awTextOut');\" onMouseOver=\"status='Copy to Clipboard'; return true;\" onMouseOut=\"status='';\">Copy to Clipboard</A>");
	document.writeln("<TEXTAREA ID=\"awTextOut\" STYLE=\"width:1px;height:1px;visibility:hidden;\">");
	document.writeln(":jsTextOut");
	document.writeln("</TEXTAREA>");
}
//--></SCRIPT>
