<iREM -- Get 'User Not Found' String -- >
<iHTML LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT cfgVal FROM _config :IfSQL WHERE cfgVar='NOTFOUND' ;" OUTPUT=":1" NOOUTPUT="Anonymous" FAILURE="Anonymous" OUTVAR="userNotFound">

<iSET mMsgID=":Messages" mPosted=":Messages" mPoster=":Messages"><iSTRCAT DST="mMsgID" SRC=".MsgID"><iSTRCAT DST="mPosted" SRC=".Posted"><iSTRCAT DST="mPoster" SRC=".Poster">

<iDEFAULT NAME="topten" VALUE="">

<iCASE ALIAS="topten" VALUE="">

  <iREM -- Gather Post Statistics -- >
  <iSET Range1="1" Range2="7" Range3="30" Range4="365">
  <iSQL LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT COUNT(:mMsgID) AS Last1 FROM :Messages :IfSQL WHERE (:mPosted > :DBNow - :Range1) ;" ALIAS="MainDB"><iSQLFETCH ALIAS="MainDB"><iSET Last1=":MainDB_Last1">
  <iSQLMORE SQL="SELECT COUNT(:mMsgID) AS Last2 FROM :Messages :IfSQL WHERE (:mPosted > :DBNow - :Range2) ;" ALIAS="MainDB"><iSQLFETCH ALIAS="MainDB"><iSET Last2=":MainDB_Last2">
  <iSQLMORE SQL="SELECT COUNT(:mMsgID) AS Last3 FROM :Messages :IfSQL WHERE (:mPosted > :DBNow - :Range3) ;" ALIAS="MainDB"><iSQLFETCH ALIAS="MainDB"><iSET Last3=":MainDB_Last3">
  <iSQLMORE SQL="SELECT COUNT(:mMsgID) AS Last4 FROM :Messages :IfSQL WHERE (:mPosted > :DBNow - :Range4) ;" ALIAS="MainDB"><iSQLFETCH ALIAS="MainDB"><iSET Last4=":MainDB_Last4">
  <iSQLMORE SQL="SELECT COUNT(:mMsgID) AS Total FROM :Messages :IfSQL ;" ALIAS="MainDB"><iSQLFETCH ALIAS="MainDB"><iSET Total=":MainDB_Total">
  <iEVAL EXPR=':Last2/7' PREC=0 OUTVAR="DailyAve"><iEVAL EXPR=':Last3/4' PREC=0 OUTVAR="WeeklyAve"><iEVAL EXPR=':Last4/12' PREC=0 OUTVAR="MonthlyAve">

  <iREM -- Gather Poster Statistics -- >
  <iSQLMORE SQL="SELECT :mPoster AS TopPoster, COUNT(:mMsgID) AS TopPosts FROM :Messages :IfSQL GROUP BY :mPoster ORDER BY COUNT(:mMsgID) DESC ;" ALIAS="MainDB"><iSQLFETCH ALIAS="MainDB">
    <iSET TopPostsTotal=":MainDB_TopPosts" TopPosterTotal="">
    <iLOOP INITIAL="1" FINAL=":LoadDB_UserNameFields">
      <iEQ NAME="tmp" VALUE=":LoadDB_UserName:i_loop" EVAL=TRUE>
      <iSTRCAT DST="TopPosterTotal" SRC='<iHTML LOGIN=":LoadDB_UserLP" DBNAME=":LoadDB_UserDSN" SQL="SELECT :tmp FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_UserID = :MainDB_TopPoster ;" OUTPUT=":1" NOOUTPUT=":userNotFound (NOP)" FAILURE=":userNotFound (Error)" ESC=FALSE EVAL=TRUE> '>
    </iLOOP>
  <iSQLMORE SQL="SELECT :mPoster AS TopPoster, COUNT(:mMsgID) AS TopPosts FROM :Messages :IfSQL WHERE (:mPosted > :DBNow - :Range1) GROUP BY :mPoster ORDER BY COUNT(:mMsgID) DESC ;" ALIAS="MainDB"><iSQLFETCH ALIAS="MainDB">
    <iSET TopPosts1=":MainDB_TopPosts" TopPoster1="">
    <iLOOP INITIAL="1" FINAL=":LoadDB_UserNameFields">
      <iEQ NAME="tmp" VALUE=":LoadDB_UserName:i_loop" EVAL=TRUE>
      <iSTRCAT DST="TopPoster1" SRC='<iHTML LOGIN=":LoadDB_UserLP" DBNAME=":LoadDB_UserDSN" SQL="SELECT :tmp FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_UserID = :MainDB_TopPoster ;" OUTPUT=":1" NOOUTPUT=":userNotFound (NOP)" FAILURE=":userNotFound (Error)" ESC=FALSE EVAL=TRUE> '>
    </iLOOP>
  <iSQLMORE SQL="SELECT :mPoster AS TopPoster, COUNT(:mMsgID) AS TopPosts FROM :Messages :IfSQL WHERE (:mPosted > :DBNow - :Range2) GROUP BY :mPoster ORDER BY COUNT(:mMsgID) DESC ;" ALIAS="MainDB"><iSQLFETCH ALIAS="MainDB">
    <iSET TopPosts2=":MainDB_TopPosts" TopPoster2="">
    <iLOOP INITIAL="1" FINAL=":LoadDB_UserNameFields">
      <iEQ NAME="tmp" VALUE=":LoadDB_UserName:i_loop" EVAL=TRUE>
      <iSTRCAT DST="TopPoster2" SRC='<iHTML LOGIN=":LoadDB_UserLP" DBNAME=":LoadDB_UserDSN" SQL="SELECT :tmp FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_UserID = :MainDB_TopPoster ;" OUTPUT=":1" NOOUTPUT=":userNotFound (NOP)" FAILURE=":userNotFound (Error)" ESC=FALSE EVAL=TRUE> '>
    </iLOOP>
  <iSQLMORE SQL="SELECT :mPoster AS TopPoster, COUNT(:mMsgID) AS TopPosts FROM :Messages :IfSQL WHERE (:mPosted > :DBNow - :Range3) GROUP BY :mPoster ORDER BY COUNT(:mMsgID) DESC ;" ALIAS="MainDB"><iSQLFETCH ALIAS="MainDB">
    <iSET TopPosts3=":MainDB_TopPosts" TopPoster3="">
    <iLOOP INITIAL="1" FINAL=":LoadDB_UserNameFields">
      <iEQ NAME="tmp" VALUE=":LoadDB_UserName:i_loop" EVAL=TRUE>
      <iSTRCAT DST="TopPoster3" SRC='<iHTML LOGIN=":LoadDB_UserLP" DBNAME=":LoadDB_UserDSN" SQL="SELECT :tmp FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_UserID = :MainDB_TopPoster ;" OUTPUT=":1" NOOUTPUT=":userNotFound (NOP)" FAILURE=":userNotFound (Error)" ESC=FALSE EVAL=TRUE> '>
    </iLOOP>

  </iSQL ALIAS="MainDB">

  <CENTER><BR><TABLE WIDTH=75% BORDER=0 CELLSPACING=2 CELLPADDING=2>

  <TR><TD COLSPAN=4><FONT FACE=":LoadDB_HeadTextFace" SIZE=":LoadDB_HeadTextSize" COLOR=":LoadDB_HeadTextColor"><B><U>Total Messages Posted:</U></B></FONT></TD></TR>
  <TR><TD><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Main Board:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:Total</FONT></B></TD><TD COLSPAN=2>&nbsp;</TD></TR>

  <TR><TD COLSPAN=4><BR></TD></TR>
  <TR><TD COLSPAN=4><FONT FACE=":LoadDB_HeadTextFace" SIZE=":LoadDB_HeadTextSize" COLOR=":LoadDB_HeadTextColor"><B><U>Messages Post Statistics:</U></B></FONT></TD></TR>
  <TR><TD><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Main Board posts in the last 24 hours:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:Last1</B></FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Daily Average:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:DailyAve<B></FONT></TD></TR>
  <TR><TD><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Main Board posts in the last 7 days:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:Last2</B></FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Weekly Average:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:WeeklyAve<B></FONT></TD></TR>
  <TR><TD><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Main Board posts in the last 30 days:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:Last3</B></FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Monthly Average:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:MonthlyAve<B></FONT></TD></TR>

  <TR><TD COLSPAN=4><BR></TD></TR>
  <TR><TD COLSPAN=4><FONT FACE=":LoadDB_HeadTextFace" SIZE=":LoadDB_HeadTextSize" COLOR=":LoadDB_HeadTextColor"><B><U>Top Poster Statistics:</U></B></FONT></TD></TR>
  <TR><TD><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Top Poster Overall:</FONT> &nbsp;<FONT FACE=":LoadDB_ListTextFace" SIZE=":LoadDB_ListTextSize" COLOR=":LoadDB_ListTextColor"><A HREF=":i_script_name?go=stats&topten=total:mLinksA">view top ten</A></FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:TopPosterTotal</B></FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"># of Posts:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:TopPostsTotal<B></FONT></TD></TR>
  <TR><TD><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Top Poster in the last 24 hours:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:TopPoster1</B></FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"># of Posts:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:TopPosts1<B></FONT></TD></TR>
  <TR><TD><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Top Poster in the last 7 days:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:TopPoster2</B></FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"># of Posts:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:TopPosts2<B></FONT></TD></TR>
  <TR><TD><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">Top Poster in the last 30 days:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:TopPoster3</B></FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"># of Posts:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:TopPosts3<B></FONT></TD></TR>

  </TABLE><BR><INPUT TYPE=BUTTON VALUE="Return to BBS" onClick="self.location=':i_script_name:mLinksQ';"></CENTER>

</iCASE ALIAS="topten" VALUE="">

<iCASE ALIAS="topten" VALUE="total">

  <CENTER><BR><TABLE WIDTH=75% BORDER=0 CELLSPACING=2 CELLPADDING=2>
  <TR><TD COLSPAN=4><FONT FACE=":LoadDB_HeadTextFace" SIZE=":LoadDB_HeadTextSize" COLOR=":LoadDB_HeadTextColor"><B><U>Top Ten Posters Overall:</U></B></FONT></TD></TR>

  <iSET Count=0>
  <iSQL LOGIN=":LOGIN" DBNAME=":DSN" SQL="SELECT :mPoster AS TopPoster, COUNT(:mMsgID) AS TopPosts FROM :Messages :IfSQL GROUP BY :mPoster ORDER BY COUNT(:mMsgID) DESC ;" ALIAS="Top"><iSQLFETCH ALIAS="Top">
    <iWHILE NOTALIAS=i_sqlempty>

      <iSET TopPostsTotal=":Top_TopPosts" TopPosterTotal="">
      <iLOOP INITIAL="1" FINAL=":LoadDB_UserNameFields">
        <iEQ NAME="tmp" VALUE=":LoadDB_UserName:i_loop" EVAL=TRUE>
        <iSTRCAT DST="TopPosterTotal" SRC='<iHTML LOGIN=":LoadDB_UserLP" DBNAME=":LoadDB_UserDSN" SQL="SELECT :tmp FROM :LoadDB_UserTable :IfUSQL WHERE :LoadDB_UserID = :Top_TopPoster ;" OUTPUT=":1" NOOUTPUT=":userNotFound (NOP)" FAILURE=":userNotFound (Error)" ESC=FALSE EVAL=TRUE> '>
      </iLOOP>

      <TR><TD><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor">:TopPosterTotal:</FONT></TD><TD ALIGN=RIGHT><FONT FACE=":LoadDB_BodyTextFace" SIZE=":LoadDB_BodyTextSize" COLOR=":LoadDB_BodyTextColor"><B>:TopPostsTotal</FONT></B></TD><TD COLSPAN=2>&nbsp;</TD></TR>

      <iEVAL EXPR=':Count + 1' OUTVAR="Count"><iIF EXPR=':Count=10'><iSET i_sqlempty=TRUE><iELSE><iSQLFETCH ALIAS="Top"></iIF>
    </iWHILE ALIAS=i_sqlempty>
  </iSQL ALIAS="Top">

  </TABLE><BR><INPUT TYPE=BUTTON VALUE="Return to Statistics" onClick="self.location=':i_script_name?go=stats:mLinksA';"> &nbsp; <INPUT TYPE=BUTTON VALUE="Return to BBS" onClick="self.location=':i_script_name:mLinksQ';"></CENTER>

</iCASE ALIAS="topten" VALUE="total">

<iCASE ALIAS="topten" VALUE="1">
</iCASE ALIAS="topten" VALUE="1">

<iCASE ALIAS="topten" VALUE="2">
</iCASE ALIAS="topten" VALUE="2">

<iCASE ALIAS="topten" VALUE="3">
</iCASE ALIAS="topten" VALUE="3">
