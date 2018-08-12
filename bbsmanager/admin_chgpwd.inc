<iIF EXPR='<iISDEF VAR="NewPassword1"> AND <iISDEF VAR="NewPassword2">' ALIAS="Change">

  <iIF COND=<iSTRCMP SRC=":NewPassword1" DST=":NewPassword2"> ALIAS="Matching">
    <iSQL LOGIN=":LOGIN" DBNAME=":dsn" SQL="UPDATE _Users SET Password=':NewPassword1' WHERE UserName = ':UserName'"><SQLFETCH></iSQL>
    <iEQ NAME="Password" VALUE=":NewPassword1">
    <iSET msg="Your password has been changed." go="default">
  <iELSE ALIAS="Matching">
    <iSET msg="Passwords do not match.  Please try again." go="default">
  </iIF ALIAS="Matching">

<iELSE ALIAS="Change">

  <FORM METHOD=POST ACTION="admin.ihtml"><INPUT TYPE=HIDDEN NAME="Login"><INPUT TYPE=HIDDEN NAME="dsn" VALUE=":dsn"><INPUT TYPE=HIDDEN NAME="UserName" VALUE=":UserName">
  <TABLE BORDER=0 CELLSPACING=0 CELLPADDING=3>
  <TR><TD>Enter your current password:</TD><TD><INPUT TYPE=PASSWORD NAME="Password"></TD></TR>
  <TR><TD>Enter your new password:</TD><TD><INPUT TYPE=PASSWORD NAME="NewPassword1"></TD></TR>
  <TR><TD>Again to verify:</TD><TD><INPUT TYPE=PASSWORD NAME="NewPassword2"></TD></TR>
  <TR><TD COLSPAN=2 ALIGN=CENTER><INPUT TYPE=SUBMIT NAME="go" VALUE="Change Password"></TD></TR>
  </TABLE>
  </FORM>

</iIF ALIAS="Change">
