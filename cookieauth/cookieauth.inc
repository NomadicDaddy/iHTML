<iREMBLOCK>
adminware Cookie Authentication Front-End v1.0.342.1
Copyright © 1999 adminware, inc.  All rights reserved.
Uses InFusion Authenticator, Copyright © 1999 On-Line Data Solutions, Inc.
</iREMBLOCK>

(cookieauth:begin)

<iIF EXPR='<iISDEF VAR="ck_usr"> AND <iISDEF VAR="ck_pwd"> AND NOT <iSTRCMP SRC=":ck_usr" DST=""> AND NOT <iSTRCMP SRC=":ck_pwd" DST=""> AND NOT <iSTRIN SRC=":ck_usr" DST="ck_usr"> AND NOT <iSTRIN SRC=":ck_pwd" DST="ck_pwd">' ALIAS="Verify">
  validformat

  <iIF COND=<iISDEF VAR="remember"> ALIAS="SetCookie">
    <iCOOKIE NAME="ck_usr" VALUE=":ck_usr" PATH="/">
    <iCOOKIE NAME="ck_pwd" VALUE=":ck_pwd" PATH="/">
    <iSET error=`Your login information is valid.  <A HREF=":url">Click here to authenticate.</A>`>
  <iELSE ALIAS="SetCookie">
    <iREDIR URL=':url'>
  </iIF ALIAS="SetCookie">

<iELSE ALIAS="Verify">
  nologinyet

  <iIF NOTCOND=<iISDEF VAR="ck_usr">><iSET ck_usr=""></iIF>
  <iIF NOTCOND=<iISDEF VAR="ck_pwd">><iSET ck_pwd=""></iIF>
  <iIF COND=<iISDEF VAR="login">><iSET error="You must enter both a username and password to continue."></iIF>

</iIF ALIAS="Verify">

(cookieauth:finish)
