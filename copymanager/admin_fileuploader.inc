<!--
adminware File Uploader for CopyManager v1.3.227.1
Copyright © 1999-2002 adminware, inc.  All rights reserved.
http://adminware.com/
-->

<iSET DoNotify=1 GoodExt="jpg;gif;png" Overwrite=1>

<iSET OrigExt=<iSTRSPAN SRC=":OrigFile" FIRST=<iEVAL EXPR='<iSTRIN SRC=":OrigFile" DST="."> + 1'> NUM=<iEVAL EXPR='<iSTRLEN SRC=":OrigFile"> - <iSTRIN SRC=":OrigFile" DST="."> + 1'>>>

<iURLENCODE SRC=':OrigFile' OUTVAR='zOrigFile'><iSET FileSize="Unavailable"><iEQ NAME=SaveAs VALUE=':imagedir\copymanager\:OrigFile' EVAL=TRUE>

<iIF EXPR='<iSTRIN SRC=":i_priv_post" DST="Content-Type:"> AND <iSTRIN SRC=":i_priv_post" DST="Content-Disposition: form-data"> AND NOT <iSTRIN SRC=":i_priv_post" DST='filename=""'> AND NOT <iSTRCMP SRC=":origFile" DST="">' ALIAS="fileUp">

  <iIF COND=<iSTRCMP SRC=":GoodExt" DST=""> ALIAS="AllExtensions"><iSET GoodExt=":OrigExt"></iIF ALIAS="AllExtensions">
	<iIF COND=<iSTRIN SRC=":goodExt" DST=":origExt"> ALIAS="goodExtension">
 
		<iFILE NAME=":saveAs" OP=EXISTS OUTVAR="fileExists">
		<iIF EXPR='NOT :fileExists OR (:fileExists AND :overwrite)' ALIAS="overwriteFile">

      <iIF EXPR=':FileExists' ALIAS="DelFile"><iFILE NAME=':SaveAs' OP=DELETE></iIF ALIAS="DelFile">
			<iGETMIMEFILE FILENAME=":saveAs" NAME=<iGETMIMENAME> EHANDLE=INLINE>
			<iFILEINFO FILE=":saveAs" INFO=SIZE OUTVAR="fileSize">
			<iIF EXPR=':fileSize GT 0' ALIAS="notEmpty">
				<iIF EXPR=':doNotify'>
					<iMAIL ADDRESS=":notifyTo" FROM=":notifyFrom" SUBJECT=":notifySubj">CopyManager Image Uploaded:	':origFile' -> ':saveAs'	Size: :fileSize bytes</iMAIL>
				</iIF>
        <iSET fumsg="Image uploaded successfully.">
			<iELSE ALIAS="notEmpty">
        <iSET fumsg="Upload failed.  Image has zero bytes.">
			</iIF ALIAS="notEmpty">

		<iELSE ALIAS="overwriteFile">

      <iSET fumsg="Upload failed.  Image already exists - rename and try again.">

		</iIF ALIAS="overwriteFile">

	<iELSE ALIAS="goodExtension">
 
    <iSET fumsg="Upload failed.  Bad extension.">

	</iIF ALIAS="goodExtension">

<iELSE ALIAS="fileUp">

  <iSET fumsg="Image not uploaded.">

</iIF ALIAS="fileUp">

<iIF COND=<iSTRCMP SRC=":fumsg" DST=""> ALIAS="NoMsg">
<iHEAPDUMP HEAP=LOCAL OUTVAR="dump">
<iREPLACE VAR="dump" SRC="<BR>" DST=":i$crlf">
<iMAIL ADDRESS=":notifyTo" FROM=":notifyFrom" SUBJECT="CopyManager File Uploader Error"><iDATETIME> CopyManager File Uploader Error = :errMsg
Error Number  = :i_error
Error Message = :i_errortext
Error Details = :i_errordetail
-----
:dump
</iMAIL>

<iSET fumsg="Unknown upload error.">
</iIF ALIAS="NoMsg">
