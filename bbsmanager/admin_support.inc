<iIF COND=<iISDEF VAR="email"> ALIAS="HasEmail">

  <iREM -- Send Request -- >
  <iMAIL ADDRESS="support@onvix.com" FROM=":email" SUBJECT="Form:  Online Support Request">
The following support request was submitted by:

Full Name:      :realname
Email Address:  :email
Contact Phone:  :phone

DSN:            :dsn
UserName:       :UserName
Password:       :Password

Request:

:request
  </iMAIL>

  <iREM -- Set Email Cookie -- >
  <iIF NOTCOND=<iISDEF VAR="ck_email"> ALIAS="EmailCookie"><iCOOKIE NAME="ck_email" VALUE=":email" PATH="/"></iIF ALIAS="EmailCookie">

  <iSET msg="Your request has been sent successfully!" go="default">

<iELSE ALIAS="HasEmail">

  <iIF NOTCOND=<iISDEF VAR="ck_email">><iSET ck_email=""></iIF>

  <SCRIPT LANGUAGE="JavaScript" TYPE="text/javascript" SRC="http://www.onvix.com/js/formcheck.js"></SCRIPT>

  <CENTER>
  <FONT COLOR="#FF0000"><B>Please use the following temporary request form to request support.</B></FONT><BR><BR>

  <FORM METHOD=POST ACTION="admin.ihtml" onSubmit = "return FormCheck(this)">
  <INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName"><INPUT TYPE=HIDDEN NAME="Password" VALUE=":Password"><INPUT TYPE=HIDDEN NAME="go" VALUE="Contact adminware Support">
  <TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=0>
  <TR><TD>Full Name:</TD><TD><INPUT TYPE=TEXT NAME="realname" SIZE=32></TD></TR>
  <TR><TD>Email Address:</TD><TD><INPUT TYPE=TEXT NAME="email" VALUE=":ck_email" SIZE=32></TD></TR>
  <TR><TD>Contact Phone:</TD><TD><INPUT TYPE=TEXT NAME="phone" SIZE=32></TD></TR>
  <TR><TD VALIGN=TOP>Request:</TD><TD><TEXTAREA NAME="request" ROWS=5 COLS=44 WRAP="VIRTUAL"></TEXTAREA></TD></TR>
  <TR><TD COLSPAN=2 ALIGN=CENTER><BR><INPUT TYPE=SUBMIT NAME="Submit" VALUE="Send Request"></TD></TR>
  </TABLE>
  </FORM>

  </CENTER>

</iIF ALIAS="HasEmail">
