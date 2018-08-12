<iREMBLOCK>
FAQ Manager Administration Module
Copyright � 1997-2002 adminware, inc.  All rights reserved.
</iREMBLOCK>

<iSET faq_ver="v1.15.107.1">

<iDEFAULT NAME="faq_img" VALUE="/images/adminware">
<iDEFAULT NAME="faq_dbup" VALUE="Administrator/zzz">
<iDEFAULT NAME="faq_font" VALUE="Arial, Helvetica, Sans-Serif">

<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=3><TR BGCOLOR=":faq_bgc"><TD><FONT FACE=":faq_font" SIZE="-1" COLOR="FFFFFF"><B>FAQ Manager Administration</B></FONT></TD></TR></TABLE><BR>
<CENTER><TABLE WIDTH=95% BORDER=0 CELLSPACING=0 CELLPADDING=0><TR><TD>

<iIF COND=<iISDEF VAR="DoMe"> ALIAS="GetInfo">

<iREM -- Move Pending Question/Answer to Active -- >
<iCASE ALIAS=DoMe VALUE="Answer Question">
	<iIF NOTCOND=<iSTRCMP SRC=":PAnswer" DST=""> ALIAS="Good">
		<iIF NOTCOND=<iSTRCMP SRC=":NewCat" DST=""> ALIAS="AddNewCat">
			<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="INSERT INTO categories (name) VALUES (':NewCat') ;">
			<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="SELECT catid FROM categories WHERE name=':NewCat' ;" OUTPUT=":1" OUTVAR="PCatID">
		</iIF ALIAS="AddNewCat">
		<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="INSERT INTO qActive (catid, question, answer) VALUES (:PCatID, ':PQuestion', ':PAnswer') ;">
		<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="DELETE FROM qPending WHERE id=:PID ;">
		<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="SELECT name FROM categories WHERE catid=:PCatID ;" OUTPUT=":1" OUTVAR="PCat">
		<iIF NOTCOND=<iSTRCMP SRC=":PNotifyEmail" DST=""> ALIAS="Notify">
			<iMAIL ADDRESS=":PNotifyEmail" BCC=":faq_mgr" FROM=":faq_emf" SUBJECT="New FAQ Question Answered!" PRIORITY="1 (Highest)"><iINCLUDE NAME=":faq_loc\notifyemail.txt"></iMAIL>
		</iIF ALIAS="Notify">
		<iEQ NAME=Stat1 VALUE="Moved Pending Question to :PCat!">
	<iELSE ALIAS="Good">
		<iSET Stat1="Failed!  Answer cannot be blank!">
	</iIF ALIAS="Good">
</iCASE ALIAS=DoMe>

<iREM -- Delete Pending Question -- >
<iCASE ALIAS=DoMe VALUE="Delete PQuestion">
	<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="DELETE FROM qPending WHERE id=:PID ;">
	<iSET Stat2="Deleted Pending Question!">
</iCASE ALIAS=DoMe>

<iREM -- Add New Question/Answer to Active -- >
<iCASE ALIAS=DoMe VALUE="Add New Question">
	<iSET z1=<iSTRCMP SRC=":NAnswer" DST=""> z2=<iSTRCMP SRC=":NQuestion" DST="">>
	<iIF EXPR="NOT :z1 AND NOT :z2" ALIAS="Good">
		<iIF NOTCOND=<iSTRCMP SRC=":NewCat" DST=""> ALIAS="AddNewCat">
			<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="INSERT INTO categories (name) VALUES (':NewCat') ;">
			<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="SELECT catid FROM categories WHERE name=':NewCat'; " OUTPUT=":1" OUTVAR="NCatID">
		</iIF ALIAS="AddNewCat">
		<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="INSERT INTO qActive (catid, question, answer) VALUES (:NCatID, ':NQuestion', ':NAnswer') ;">
		<iEQ NAME=ActionStat VALUE="Added New Question to :ShowCat!">
	<iELSE ALIAS="Good">
		<iSET ActionStat="Failed!  The question and/or answer cannot be blank!">
	</iIF ALIAS="Good">
</iCASE ALIAS=DoMe>

<iREM -- Add New Category -- >
<iCASE ALIAS=DoMe VALUE="Add New Category">
	<iIF NOTCOND=<iSTRCMP SRC=":NewCat" DST="">>
		<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="INSERT INTO categories (name) VALUES (':NewCat') ;">
		<iSET ActionStat="Added New Category!">
	<iELSE>
		<iSET ActionStat="Failed!  Category name cannot be blank!">
	</iIF>
</iCASE ALIAS=DoMe>

<iREM -- Modify Question -- >
<iCASE ALIAS=DoMe VALUE="Modify Question">
	<iSET z1=<iSTRCMP SRC=":NAnswer" DST=""> z2=<iSTRCMP SRC=":NQuestion" DST="">>
	<iIF EXPR="NOT :z1 AND NOT :z2" ALIAS="Good">
		<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="UPDATE qActive SET question=':NQuestion', answer=':NAnswer' WHERE id=:NID ;">
		<iEQ NAME=ActionStat VALUE="Saved Modifications to Question!">
	<iELSE ALIAS="Good">
		<iSET ActionStat="Failed!  The question and/or answer cannot be blank!">
	</iIF ALIAS="Good">
</iCASE ALIAS=DoMe>

<iREM -- Delete Question -- >
<iCASE ALIAS=DoMe VALUE="Delete Question">
	<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="DELETE FROM qActive WHERE id=:NID ;">
	<iEQ NAME=ActionStat VALUE="Question Deleted!">
</iCASE ALIAS=DoMe>

<iREM -- Rename Category -- >
<iCASE ALIAS=DoMe VALUE="Rename Category">
	<iIF NOTCOND=<iSTRCMP SRC=":NewName" DST=""> ALIAS="Good">
		<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="UPDATE categories SET name=':NewName' WHERE catid=:NCatID ;">
		<iEQ NAME=ActionStat VALUE="Renamed :ShowCat to :NewName!">
	<iELSE ALIAS="Good">
		<iSET ActionStat="Failed!  The new catagory name cannot be blank!">
	</iIF ALIAS="Good">
</iCASE ALIAS=DoMe>

<iREM -- Delete Category -- >
<iCASE ALIAS=DoMe VALUE="Delete Category">
	<iIF NOTCOND=<iSTRCMP SRC=":NewName" DST=""> ALIAS="Good">
		<iIF COND=<iSTRCMP SRC=":Orphans" DST="Delete"> ALIAS="DoOrphans">
			<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="DELETE FROM categories WHERE catid=:FromCatID ;">
			<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="DELETE FROM qActive WHERE catid=:FromCatID ;">
			<iEQ NAME=ActionStat VALUE="Deleted :ShowCat and orphan questions!">
		<iELSE ALIAS="DoOrphans">
			<iIF NOTCOND=<iSTRCMP SRC=":ToCatID"> DST="">>
				<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="DELETE FROM categories WHERE catid=:FromCatID ;">
				<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="UPDATE qActive SET catid=:ToCatID WHERE catid=:FromCatID ;">
				<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="SELECT name FROM categories WHERE catid = :ToCatID ;" OUTPUT=":1" OUTVAR="toCat">
				<iEQ NAME=ActionStat VALUE="Deleted :ShowCat and moved orphan questions to :toCat!">
			<iELSE>
				<iEQ NAME=ActionStat VALUE="Could not delete :ShowCat and move questions.	Category to move to must be specified.">
			</iIF>
		</iIF ALIAS="DoOrphans">
	<iELSE ALIAS="Good">
		<iSET ActionStat="Failed!  The new catagory name cannot be blank!">
	</iIF ALIAS="Good">
</iCASE ALIAS=DoMe>

</iIF ALIAS="GetInfo">

<iREM -- Show Next Pending Question -- >
<HR NOSHADE WIDTH=95%><CENTER><FONT SIZE="+1" COLOR="#0000FF">Answer/Modify/Delete Pending Questions</FONT><BR>
<iSET PQCount=0>
<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="SELECT COUNT(*) FROM qPending ;" OUTPUT=":1" OUTVAR="pQCount">
# of Pending Questions: <B>:pQCount</B><BR></CENTER>
<iIF EXPR=":pQCount > 0" ALIAS="DoAnswerPQ">
	<iSQL LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="SELECT id, question, notifyEmail FROM qPending ;" ALIAS="getQs"><iSQLFETCH ALIAS="getQs">
	<iEQ NAME="PID" VALUE=":getQs_ID">
	<iEQ NAME="PQuestion" VALUE=":getQs_Question">
	<iEQ NAME="PNotifyEmail" VALUE=":getQs_NotifyEmail">
	</iSQL ALIAS="getQs">
<FORM ACTION=':i_script_name' METHOD=POST>
<TABLE WIDTH="100%" BORDER=0 CELLSPACING=2 CELLPADDING=2>
<TR><TD><B>Current Question</B></TD><TD><TEXTAREA WRAP=SOFT NAME="PQuestion" ROWS=2 COLS=45>:PQuestion</TEXTAREA></TD></TR>
<TR><TD><B>Submitted By</B></TD><TD><INPUT TYPE=TEXT NAME="PNotifyEmail" SIZE=45 VALUE=":PNotifyEmail"></TD></TR>
<TR><TD><B>Answer</B></TD><TD><TEXTAREA WRAP=SOFT NAME="PAnswer" ROWS=5 COLS=45></TEXTAREA></TD></TR>
<TR>
	<TD><B>Add to Category</B></TD>
	<TD><SELECT NAME="PCatID">
		<iSQL LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="SELECT catid, name FROM categories ;" ALIAS="getCs"><iSQLFETCH ALIAS="getCs">
		<iWHILE NOTALIAS=i_sqlempty>
			<OPTION VALUE=":getCs_CatID">:getCs_Name
			<iSQLFETCH ALIAS="getCs">
		</iWHILE ALIAS=i_sqlempty>
		</iSQL ALIAS="getCs">
	</SELECT></TD>
</TR>
<TR>
	<TD><B>Make New Category</B></TD>
	<TD><INPUT TYPE=TEXT NAME="NewCat" SIZE=25></TD>
</TR>
</TABLE><BR>
<INPUT TYPE=HIDDEN NAME="PID" VALUE=":PID"><INPUT TYPE=SUBMIT NAME="DoMe" VALUE="Answer Question"></FORM>
<FORM ACTION=':i_script_name' METHOD=POST><INPUT TYPE=HIDDEN NAME="PID" VALUE=":PID"><INPUT TYPE=SUBMIT NAME="DoMe" VALUE="Delete PQuestion"></FORM>
</iIF ALIAS="DoAnswerPQ">
<iIF COND=<iISDEF VAR="Stat1">><CENTER><FONT COLOR="#FF0000" SIZE="+1"><B>:Stat1</B></FONT></CENTER></iIF>
<iIF COND=<iISDEF VAR="Stat2">><CENTER><FONT COLOR="#FF0000" SIZE="+1"><B>:Stat2</B></FONT></CENTER></iIF>

<iREM -- Browse/Search Questions -- >
<HR NOSHADE WIDTH=95%><CENTER><FONT SIZE="+1" COLOR="#0000FF">Browse/Search Questions</FONT><BR></CENTER>
<iIF COND=<iISDEF VAR="ActionStat">><CENTER><BR><FONT COLOR="#FF0000" SIZE="+1"><B>:ActionStat</B></FONT><BR></CENTER></iIF><BR>
<iSQL LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="SELECT CatID,Name FROM Categories ;" ALIAS="Cats">
<iSQLFETCH ALIAS="Cats"><iIF COND=:i_sqlempty><iSET t1=TRUE><iELSE><iSET t1=FALSE></iIF>
<iWHILE NOTALIAS=t1>
	<iEQ NAME="eCats_Name" VALUE=<iURLENCODE SRC=":Cats_Name"> EVAL=TRUE>
	<iIF COND=<iSTRCMP SRC=":ShowCat" DST=":Cats_Name"> ALIAS="ShowCats">
		<A HREF=":i_script_name?Action=Add&ShowCat=:eCats_Name"><IMG SRC=":faq_img/btn_add.gif" ALT="Add New Question in this Category" WIDTH=23 HEIGHT=11 BORDER=0 HSPACE=0 VSPACE=0></A>
		<A HREF=":i_script_name?Action=Edit&ShowCat=:eCats_Name"><IMG SRC=":faq_img/btn_edit.gif" ALT="Rename Category" WIDTH=23 HEIGHT=11 BORDER=0 HSPACE=0 VSPACE=0></A>
		<A HREF=":i_script_name?Action=Delete&ShowCat=:eCats_Name"><IMG SRC=":faq_img/btn_del.gif" ALT="Delete Category" WIDTH=23 HEIGHT=11 BORDER=0 HSPACE=0 VSPACE=0></A>
		<A HREF=":i_script_name"><IMG SRC=":faq_img/minus.gif" ALT="-" WIDTH=10 HEIGHT=10 BORDER=0 HSPACE=5 VSPACE=0></A>:Cats_Name<BR>

<iEQ NAME="z1" VALUE=<iSTRCMP SRC=":Action" DST="Add">><iEQ NAME="z2" VALUE=<iISDEF VAR="ShowCat">>
<iIF EXPR=":z1 AND :z2" ALIAS="Add2Cat">
	<iREM -- Add New Question in this Category -- >
	<HR NOSHADE WIDTH=50%><CENTER>Add New Question in <B>:ShowCat</B><FORM ACTION=':i_script_name' METHOD=POST>
	<TABLE BORDER=0 CELLSPACING=2 CELLPADDING=2>
	<TR><TD><B>Question</B></TD><TD><TEXTAREA WRAP=SOFT NAME="NQuestion" ROWS=2 COLS=45></TEXTAREA></TD></TR>
	<TR><TD><B>Answer</B></TD><TD><TEXTAREA WRAP=SOFT NAME="NAnswer" ROWS=5 COLS=45></TEXTAREA></TD></TR>
	</TABLE><INPUT TYPE=HIDDEN NAME="ShowCat" VALUE=":Cats_Name"><INPUT TYPE=HIDDEN NAME="NCatID" VALUE=":Cats_CatID"><INPUT TYPE=HIDDEN NAME="NewCat" VALUE=""><INPUT TYPE=SUBMIT NAME="DoMe" VALUE="Add New Question"></FORM></CENTER><HR NOSHADE WIDTH=50%>
</iIF ALIAS="Add2Cat">

<iIF COND=<iSTRCMP SRC=":Action" DST="Edit"> ALIAS="RenameCat">
	<iIF NOTCOND=<iISDEF VAR="ShowQ">>
		<iREM -- Rename Category -- >
		<HR NOSHADE WIDTH=50%><CENTER>Rename <B>:ShowCat</B> to<FORM ACTION=':i_script_name' METHOD=POST>
		<INPUT TYPE=TEXT NAME="NewName" SIZE=25><INPUT TYPE=HIDDEN NAME="ShowCat" VALUE=":Cats_Name"><INPUT TYPE=HIDDEN NAME="NCatID" VALUE=":Cats_CatID"> <INPUT TYPE=SUBMIT NAME="DoMe" VALUE="Rename Category"></FORM></CENTER><HR NOSHADE WIDTH=50%>
	</iIF>
</iIF ALIAS="RenameCat">

<iIF COND=<iSTRCMP SRC=":Action" DST="Delete"> ALIAS="DeleteCat">
	<iIF NOTCOND=<iISDEF VAR="ShowQ"> ALIAS="Go">
		<iREM -- Delete Category -- >
		<HR NOSHADE WIDTH=50%><CENTER>Delete <B>:ShowCat</B><BR><BR>How should I handle orphaned questions?<FORM ACTION=':i_script_name' METHOD=POST>
		<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0>
		<TR><TD><INPUT TYPE=RADIO NAME="Orphans" VALUE="Delete" CHECKED>Delete</TD><TD>&nbsp;</TD></TR>
		<TR><TD><INPUT TYPE=RADIO NAME="Orphans" VALUE="Move">Move to </TD><TD>
		<SELECT NAME="ToCatID"><OPTION VALUE="">
		<iSQL LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="SELECT catid, name FROM categories ;" ALIAS="getCs"><iSQLFETCH ALIAS="getCs">
		<iWHILE NOTALIAS=i_sqlempty>
			<iIF NOTCOND=<iSTRCMP SRC=":ShowCat" DST=":getCs_Name">><OPTION VALUE=":getCs_CatID">:getCs_Name</iIF>
			<iSQLFETCH ALIAS="getCs">
		</iWHILE ALIAS=i_sqlempty>
		</iSQL ALIAS="getCs">
		</SELECT></TD></TR></TABLE><BR>
		<INPUT TYPE=HIDDEN NAME="FromCatID" VALUE=":Cats_CatID">
		<INPUT TYPE=HIDDEN NAME="ShowCat" VALUE=":Cats_Name">
		<INPUT TYPE=SUBMIT NAME="DoMe" VALUE="Delete Category"></FORM></CENTER><HR NOSHADE WIDTH=50%>
	</iIF ALIAS="Go">
</iIF ALIAS="DeleteCat">

		<iSQL LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="SELECT id, question, answer FROM qActive WHERE catid = :Cats_CatID ;" ALIAS="Qs">
		<iSQLFETCH ALIAS="Qs"><iIF COND=:i_sqlempty><iSET t2=TRUE><iELSE><iSET t2=FALSE><iSET QCount=0><BR></iIF>
		<iWHILE NOTALIAS=t2>
			<iSET QCount=<iMATH A=:QCount B=1 O="+">>

<iEQ NAME="z1" VALUE=<iISDEF VAR="Action">><iEQ NAME="z2" VALUE=<iISDEF VAR="ShowQ">><iEQ NAME="z3" VALUE=<iSTRCMP SRC=":ShowQ" DST=":Qs_ID">>
<iIF EXPR=":z1 AND :z2 AND :z3" ALIAS="EditDelQ">
	<iEQ NAME="z1" VALUE=<iSTRCMP SRC=":Action" DST="Edit">><iEQ NAME="z2" VALUE=<iISDEF VAR="ShowQ">><iEQ NAME="z3" VALUE=<iSTRCMP SRC=":ShowQ" DST=":Qs_ID">>
	<iIF EXPR=":z1 AND :z2 AND :z3" ALIAS="EditQ">
		<iREM -- Modify Question -- >
		<HR NOSHADE WIDTH=50%><CENTER>Modify Question<FORM ACTION=':i_script_name' METHOD=POST>
		<TABLE BORDER=0 CELLSPACING=2 CELLPADDING=2>
		<TR><TD><B>Question</B></TD><TD><TEXTAREA WRAP=SOFT NAME="NQuestion" ROWS=2 COLS=45>:Qs_Question</TEXTAREA></TD></TR>
		<TR><TD><B>Answer</B></TD><TD><TEXTAREA WRAP=SOFT NAME="NAnswer" ROWS=5 COLS=45>:Qs_Answer</TEXTAREA></TD></TR>
		</TABLE><INPUT TYPE=HIDDEN NAME="ShowCat" VALUE=":Cats_Name"><INPUT TYPE=HIDDEN NAME="NID" VALUE=":Qs_ID"><INPUT TYPE=SUBMIT NAME="DoMe" VALUE="Modify Question"></FORM></CENTER><HR NOSHADE WIDTH=50%>
	</iIF ALIAS="EditQ">
	<iEQ NAME="z1" VALUE=<iSTRCMP SRC=":Action" DST="Delete">><iEQ NAME="z2" VALUE=<iISDEF VAR="ShowQ">><iEQ NAME="z3" VALUE=<iSTRCMP SRC=":ShowQ" DST=":Qs_ID">>
	<iIF EXPR=":z1 AND :z2 AND :z3" ALIAS="DeleteQ">
		<iREM -- Modify Question -- >
		<HR NOSHADE WIDTH=50%><CENTER>Are you sure you want to delete this question?<BR><BR><B>:Qs_Question</B>
		<FORM ACTION=':i_script_name' METHOD=POST><INPUT TYPE=HIDDEN NAME="ShowCat" VALUE=":Cats_Name"><INPUT TYPE=HIDDEN NAME="NID" VALUE=":Qs_ID">
		<INPUT TYPE=SUBMIT NAME="DoMe" VALUE="Delete Question"></FORM></CENTER><HR NOSHADE WIDTH=50%>
	</iIF ALIAS="DeleteQ">
<iELSE ALIAS="EditDelQ">

			<IMG SRC=":faq_img/space.gif" ALT=" " WIDTH=10 HEIGHT=10 BORDER=0 HSPACE=0 VSPACE=0>
			<A HREF=":i_script_name?Action=Edit&ShowCat=:eCats_Name&ShowQ=:Qs_ID"><IMG SRC=":faq_img/btn_edit.gif" ALT="Edit Question" WIDTH=23 HEIGHT=11 BORDER=0 HSPACE=0 VSPACE=0></A>
			<A HREF=":i_script_name?Action=Delete&ShowCat=:eCats_Name&ShowQ=:Qs_ID"><IMG SRC=":faq_img/btn_del.gif" ALT="Delete Question" WIDTH=23 HEIGHT=11 BORDER=0 HSPACE=0 VSPACE=0></A>
			<FONT SIZE="-1"><B>:QCount</B>. <A HREF=":i_script_name?ShowCat=:eCats_Name&ShowQ=:Qs_ID">:Qs_Question</A></FONT>
			<iIF COND=<iSTRCMP SRC=":ShowQ" DST=":Qs_ID"> ALIAS="ShowQs">
				<BR><BR><BLOCKQUOTE><B>:Qs_Answer</B></BLOCKQUOTE>
			<iELSE ALIAS="ShowQs"><BR>
			</iIF ALIAS="ShowQs">

</iIF ALIAS="EditDelQ">

			<iSQLFETCH ALIAS="Qs"><iIF COND=:i_sqlempty><iSET t2=TRUE><BR><iELSE><iSET t2=FALSE></iIF>
		</iWHILE ALIAS=t2>
		</iSQL ALIAS="Qs">
	<iELSE ALIAS="ShowCats">
		<A HREF=":i_script_name?Action=Add&ShowCat=:eCats_Name"><IMG SRC=":faq_img/btn_add.gif" ALT="Add New Question in this Category" WIDTH=23 HEIGHT=11 BORDER=0 HSPACE=0 VSPACE=0></A>
		<A HREF=":i_script_name?Action=Edit&ShowCat=:eCats_Name"><IMG SRC=":faq_img/btn_edit.gif" ALT="Rename Category" WIDTH=23 HEIGHT=11 BORDER=0 HSPACE=0 VSPACE=0></A>
		<A HREF=":i_script_name?Action=Delete&ShowCat=:eCats_Name"><IMG SRC=":faq_img/btn_del.gif" ALT="Delete Category" WIDTH=23 HEIGHT=11 BORDER=0 HSPACE=0 VSPACE=0></A>
		<A HREF=":i_script_name?ShowCat=:eCats_Name"><IMG SRC=":faq_img/plus.gif" ALT="+" WIDTH=10 HEIGHT=10 BORDER=0 HSPACE=5 VSPACE=0>:Cats_Name</A><BR>
	</iIF ALIAS="ShowCats">
	<iSQLFETCH ALIAS="Cats"><iIF COND=:i_sqlempty><iSET t1=TRUE><iELSE><iSET t1=FALSE></iIF>
</iWHILE ALIAS=t1>

<iEQ NAME="z1" VALUE=<iSTRCMP SRC=":Action" DST="Add">><iEQ NAME="z2" VALUE=<iISDEF VAR="ShowCat">>
<iIF EXPR=":z1 AND NOT :z2">
	<iREM -- Add New Category -- >
	<HR NOSHADE WIDTH=50%><CENTER>Add New Category<FORM ACTION=':i_script_name' METHOD=POST>
	<TABLE BORDER=0 CELLSPACING=2 CELLPADDING=2>
	<TR><TD><B>New Category</B></TD><TD><INPUT TYPE=TEXT NAME="NewCat" SIZE=25></TD></TR>
	</TABLE><BR>
	<INPUT TYPE=SUBMIT NAME="DoMe" VALUE="Add New Category"></FORM></CENTER><HR NOSHADE WIDTH=50%>
<iELSE>
	<BR><A HREF=":i_script_name?Action=Add"><IMG SRC=":faq_img/btn_add.gif" ALT="Add New Category" WIDTH=23 HEIGHT=11 BORDER=0 HSPACE=0 VSPACE=0></A>
	<IMG SRC=":faq_img/space.gif" ALT=" " WIDTH=5 HEIGHT=10 BORDER=0 HSPACE=0 VSPACE=0>New Category
</iIF>

</iSQL ALIAS="Cats">

<iEQ NAME="z1" VALUE=<iISDEF VAR="searchfor">><iEQ NAME="z2" VALUE=<iSTRCMP SRC=":searchfor" DST="">>
<iIF EXPR=":z1 AND NOT :z2" ALIAS="Searched">
	<BR><BR><B>Matches for ':searchfor':</B><BR><BR>
	<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=0>
	<iSQL LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="SELECT * FROM qActive WHERE question LIKE '%:searchfor%' OR answer LIKE '%:searchfor%' ORDER BY catid ;" ALIAS="Matches">
	<iSQLFETCH ALIAS="Matches"><iSET QCount=0>
	<iWHILE NOTALIAS=i_sqlempty>
		<iEVAL EXPR=':qCount + 1' OUTVAR="qCount">
		<iHTML LOGIN=":faq_dbup" DBNAME=":faq_dsn" SQL="SELECT name FROM categories WHERE catid=:Matches_CatID ;" OUTPUT=":1" OUTVAR="z">
		<iEQ NAME="eCats_Name" VALUE=<iURLENCODE SRC=":z"> EVAL=TRUE>
		<TR>
			<TD><IMG SRC=":faq_img/space.gif" ALT=" " WIDTH=10 HEIGHT=10 BORDER=0 HSPACE=0 VSPACE=0><FONT SIZE="-1"><B>:z</B></FONT></TD>
			<TD><A HREF=":i_script_name?ShowCat=:eCats_Name&ShowQ=:Matches_ID"><FONT SIZE="-1">:Matches_Question</FONT></A></TD>
		</TR>
		<iSQLFETCH ALIAS="Matches">
	</iWHILE ALIAS=i_sqlempty>
	</TABLE><BR><B>
	<iIF EXPR=":QCount LT 1">None
	<iELSEIF EXPR=":QCount > 1">:QCount Matches
	<iELSE>1 Match
	</iIF> Found!</B><BR>
	</iSQL ALIAS="Matches">
</iIF ALIAS="Searched">

<iSET searchfor="">
<FORM ACTION=':i_script_name' METHOD=GET><TABLE BORDER=0 CELLSPACING=2 CELLPADDING=2>
<TR><TD><FONT SIZE="-1"><B>Search For</B></FONT></TD><TD><INPUT TYPE=TEXT NAME="searchfor" SIZE=30 VALUE=":searchfor"></TD><TD><INPUT TYPE=SUBMIT NAME="Search" VALUE="Go!"></TD></TR>
</TABLE></FORM>

</TD></TR></TABLE></CENTER>
<TABLE WIDTH="100%" BORDER=0 CELLSPACING=0 CELLPADDING=3><TR BGCOLOR=":faq_bgc" ALIGN=RIGHT><TD COLSPAN=2><FONT FACE=":faq_font" SIZE="-1" COLOR="FFFFFF"><B>FAQ Manager :faq_ver</B></FONT></TD></TR><TR><TD VALIGN=TOP><FONT FACE=":faq_font" SIZE="-2"><B>Copyright &copy; 1997-2000 adminware, inc. &nbsp;All rights reserved.</B></FONT></TD><TD ALIGN=RIGHT VALIGN=TOP><FONT FACE=":faq_font" SIZE="-2"><B><A HREF="http://www.faqmanager.com/" onMouseOver="status='FAQ Manager'; return true;" onMouseOut="status='';">http://www.faqmanager.com/</A></B></FONT></TD></TR></TABLE><BR>

<CENTER>For support or suggestions, please <A HREF="mailto:support@faqmanager.com" onMouseOver="status='FAQ Manager Support'; return true;" onMouseOut="status='';">click here</A>.<CENTER><BR>
