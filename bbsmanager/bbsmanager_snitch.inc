<iIF COND=<iSTRCMP SRC=":go" DST="snitch"> ALIAS="Snitch"><BR>
  <iIF COND=<iISDEF VAR="Confirmed"> ALIAS="YesDoIt">
    <iREM -- Escape Quotes in Body -- >
    <iREPLACE VAR="Body" SRC="'" DST="''">
    <iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL=`UPDATE :Messages SET Body=':Body' WHERE MsgID=:msgid ;` NOOUTPUT="Message #<B>:msgid</B> has been updated." FAILURE="UPDATE ERROR: :i_sqlerrortext" OUTVAR="msg">
    <iREPLACE VAR="msg" SRC=":IsSQLError" DST="Update failed.">
  <iELSE ALIAS="YesDoIt">
    <iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT Body FROM :Messages :IfSQL WHERE MsgID = :msgid ;" OUTPUT=":1" OUTVAR="Body">
    <FORM METHOD=POST ACTION=':i_script_name#:msgid'><INPUT TYPE=HIDDEN NAME="username" VALUE=":bbs_un">
    <FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><TEXTAREA NAME="Body" WRAP=SOFT ROWS=15 COLS=58>:Body</TEXTAREA></FONT><BR><BR>
    <INPUT TYPE=HIDDEN NAME="ID" VALUE=":id"><INPUT TYPE=HIDDEN NAME="msgid" VALUE=":msgid"><INPUT TYPE=HIDDEN NAME="go" VALUE="editpost"><INPUT TYPE=HIDDEN NAME="Confirmed" VALUE="1">
    <INPUT TYPE=SUBMIT VALUE=" Save Changes ">
    </FORM>
  </iIF ALIAS="YesDoIt">
</iIF ALIAS="Snitch">


<iIF COND=<iISDEF VAR="email"> ALIAS="HasEmail">

  <iREM -- Determine adminware Program -- >
  <iIF COND=<iISDEF VAR="AWPV">><iSET ProgName=":AWPV"><iELSEIF COND=<iISDEF VAR="AWPAV">><iSET ProgName=":AWPAV"><iELSE><iSET ProgName="(unknown)"></iIF>

  <iREM -- Send Request -- >
  <iMAIL ADDRESS="support@adminware.com" FROM=":email" SUBJECT="adminware :ProgName Support Request">The following support request for :ProgName was submitted by:

Full Name:      :realname
Email Address:  :email
Contact Phone:  :phone

DSN:            :DSN
UserName:       :UserName
Password:       :Password

Request:

:request</iMAIL>

  <iREM -- Send Response -- >
  <iMAIL ADDRESS=":email" FROM="support@adminware.com" SUBJECT="adminware :ProgName Support Request">Thank you for contacting adminware!

We have received your support request for :ProgName and will respond as soon as possible.

Thank you!

-- 
adminware Support
http://adminware.com/</iMAIL>

  <iREM -- Set Email Cookie -- >
  <iIF NOTCOND=<iISDEF VAR="ck_email"> ALIAS="EmailCookie"><iCOOKIE NAME="ck_email" VALUE=":email" PATH="/"></iIF ALIAS="EmailCookie">

  <iSET msg="Your request has been sent successfully!" go="default">

<iELSE ALIAS="HasEmail">

  <iIF NOTCOND=<iISDEF VAR="ck_email">><iSET ck_email=""></iIF>

  <SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript" SRC="http://adminware.com/js/support_request.js"></SCRIPT>

  <CENTER>
  <BR><FONT COLOR="#FF0000"><B>Please use the following request form to request support regarding this adminware application only.</B></FONT><BR><BR>
  If your question, comment or issue is regarding something other than <B>:AWPV</B>, please contact the webmaster of the site you're on.<BR><BR>
  You may use this form to request support, point out a bug or problem or to make a comment or suggestion.  We value your feedback.<BR><BR>

  <FORM METHOD=POST ACTION=:i_script_name onSubmit = "return FormCheck(this)">
  <INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="DSN" VALUE=":DSN"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="go" VALUE="Contact adminware Support">
  <TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=0>
  <TR><TD>Full Name:</TD><TD><INPUT TYPE=TEXT NAME="realname" SIZE=32></TD></TR>
  <TR><TD>Email Address:</TD><TD><INPUT TYPE=TEXT NAME="email" VALUE=":ck_email" SIZE=32></TD></TR>
  <TR><TD>Contact Phone:</TD><TD><INPUT TYPE=TEXT NAME="phone" SIZE=32></TD></TR>
  <TR><TD VALIGN=TOP>Request:</TD><TD><TEXTAREA NAME="request" ROWS=5 COLS=44 WRAP="VIRTUAL"></TEXTAREA></TD></TR>
  <TR><TD COLSPAN=2 ALIGN=CENTER><BR><INPUT TYPE=SUBMIT NAME="Submit" VALUE="Send Request"><INPUT TYPE=BUTTON NAME="Abort" VALUE="Abort" onClick="self.location=':i_script_name?Login=1&msg=Support%20request%20cancelled.&UserName=:UserName&Password=:Password';"></TD></TR>
  </TABLE>
  </FORM>

  </CENTER>

</iIF ALIAS="HasEmail">
