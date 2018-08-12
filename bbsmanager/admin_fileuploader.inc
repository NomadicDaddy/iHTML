<iREMBLOCK>
adminware File Uploader for BBSManager v1.0.259.1
Copyright © 1999 adminware, inc.  All rights reserved.
</iREMBLOCK>

<iSET DoNotify=1 GoodExt="jpg;gif;png" Overwrite=1>

<iSET OrigExt=<iSTRSPAN SRC=":OrigFile" FIRST=<iEVAL EXPR='<iSTRIN SRC=":OrigFile" DST="."> + 1'> NUM=<iEVAL EXPR='<iSTRLEN SRC=":OrigFile"> - <iSTRIN SRC=":OrigFile" DST="."> + 1'>>>

<iURLENCODE SRC=':OrigFile' OUTVAR='zOrigFile'><iSET FileSize="Unavailable"><iEQ NAME=SaveAs VALUE=':imagedir\bbsmanager\:OrigFile' EVAL=TRUE>

<iIF EXPR='<iSTRIN SRC=":i_priv_post" DST="Content-Type:"> AND <iSTRIN SRC=":i_priv_post" DST="Content-Disposition: form-data"> AND NOT <iSTRIN SRC=":i_priv_post" DST='filename=""'> AND NOT <iSTRCMP SRC=":OrigFile" DST="">' ALIAS="FileUp">

  <iIF COND=<iSTRCMP SRC=":GoodExt" DST=""> ALIAS="AllExtensions"><iSET GoodExt=":OrigExt"></iIF ALIAS="AllExtensions">
  <iIF COND=<iSTRIN SRC=":GoodExt" DST=":OrigExt"> ALIAS="GoodExtension">
 
   <iSET FileExists=<iFILE NAME=':SaveAs' OP=EXISTS>>
    <iIF EXPR='NOT :FileExists OR (:FileExists AND :Overwrite)' ALIAS="OverwriteFile">

      <iIF EXPR=':FileExists' ALIAS="DelFile"><iFILE NAME=':SaveAs' OP=DELETE></iIF ALIAS="DelFile">
      <iGETMIMEFILE FILENAME=':SaveAs' NAME=<iGETMIMENAME> EHANDLE=INLINE><iSET FileSize=<iFILEINFO FILE=':SaveAs' INFO=SIZE>>
      <iIF EXPR=':FileSize GT 0' ALIAS="NotEmpty">
        <iIF EXPR=':DoNotify'><iMAIL ADDRESS=':NotifyTo' FROM=':NotifyFrom' SUBJECT="BBSManager Image Uploaded">Image Uploaded:  ':OrigFile' -> ':SaveAs'  Size: :FileSize bytes</iMAIL></iIF>
        <iSET fumsg="Image uploaded successfully.">
      <iELSE ALIAS="NotEmpty">
        <iSET fumsg="Upload failed.  Image has zero bytes.">
      </iIF ALIAS="NotEmpty">

    <iELSE ALIAS="OverwriteFile">

      <iSET fumsg="Upload failed.  Image already exists - rename and try again.">

    </iIF ALIAS="OverwriteFile">

  <iELSE ALIAS="GoodExtension">
 
    <iSET fumsg="Upload failed.  Bad extension.">

  </iIF ALIAS="GoodExtension">

<iELSE ALIAS="FileUp">

  <iSET fumsg="Image not uploaded.">

</iIF ALIAS="FileUp">

<iIF COND=<iSTRCMP SRC=":fumsg" DST=""> ALIAS="NoMsg">
<iHEAPDUMP HEAP=LOCAL OUTVAR="dump"><iREPLACE VAR="dump" SRC="<BR>" DST="
">
<iMAIL ADDRESS=":NotifyTo" FROM=":NotifyFrom" SUBJECT="BBSManager File Uploader Error">
<iDATETIME> File Uploader for BBSManager Error = :ErrMsg
Error Number  = :i_error
Error Message = :i_errortext
Error Details = :i_errordetail
-----
:dump
</iMAIL>

<iSET fumsg="Unknown upload error.">
</iIF ALIAS="NoMsg">
