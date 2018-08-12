<iREMBLOCK>
adminware FormProcessor v1.0.346.3
Copyright © 1999-2002 adminware, inc.  All rights reserved.
</iREMBLOCK>

<iREM SQLROW DBNAME=":dsn" TABLE=":table" OP=INSERT>

<iIF NOTCOND=<iISDEF VAR="Name">><iSET Name=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Company">><iSET Company=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Address">><iSET Address=""></iIF>
<iIF NOTCOND=<iISDEF VAR="City">><iSET City=""></iIF>
<iIF NOTCOND=<iISDEF VAR="State">><iSET State=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Zip">><iSET Zip=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Phone">><iSET Phone=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Fax">><iSET Fax=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Country">><iSET Country=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Email">><iSET Email=""></iIF>
<iIF NOTCOND=<iISDEF VAR="category">><iSET category=""></iIF>
<iIF NOTCOND=<iISDEF VAR="contact_via">><iSET contact_via=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Word_of_Mouth">><iSET Word_of_Mouth=""></iIF>
<iIF NOTCOND=<iISDEF VAR="sweets_sweets_internet">><iSET sweets_sweets_internet=""></iIF>
<iIF NOTCOND=<iISDEF VAR="truck_800number">><iSET truck_800number=""></iIF>
<iIF NOTCOND=<iISDEF VAR="building_systems_magazine">><iSET building_systems_magazine=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Res_Build_prod_4c_ad">><iSET Res_Build_prod_4c_ad=""></iIF>
<iIF NOTCOND=<iISDEF VAR="thomas_register">><iSET thomas_register=""></iIF>
<iIF NOTCOND=<iISDEF VAR="SBS_web_page">><iSET SBS_web_page=""></iIF>
<iIF NOTCOND=<iISDEF VAR="mortgage_lenders">><iSET mortgage_lenders=""></iIF>
<iIF NOTCOND=<iISDEF VAR="link_from_web_page">><iSET link_from_web_page=""></iIF>
<iIF NOTCOND=<iISDEF VAR="yellow_pages">><iSET yellow_pages=""></iIF>
<iIF NOTCOND=<iISDEF VAR="product_file_dir_listing">><iSET product_file_dir_listing=""></iIF>
<iIF NOTCOND=<iISDEF VAR="other">><iSET other=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Free_House_Package_Catalog">><iSET Free_House_Package_Catalog=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Information_Kit">><iSET Information_Kit=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Kit_Payment">><iSET Kit_Payment=""></iIF>
<iIF NOTCOND=<iISDEF VAR="Comments">><iSET Comments=""></iIF>

<iREM -- Insert data into table -- >
<iSQL DBNAME=":dsn" SQL="INSERT INTO :table (Name,Company,Address,City,State,Zip,Phone,Fax,Country,Email,category,contact_via,Word_of_Mouth,sweets_sweets_internet,truck_800number,building_systems_magazine,Res_Build_prod_4c_ad,thomas_register,SBS_web_page,mortgage_lenders,link_from_web_page,yellow_pages,product_file_dir_listing,other,Free_House_Package_Catalog,Information_Kit,Kit_Payment,Comments) VALUES (':Name',':Company',':Address',':City',':State',':Zip',':Phone',':Fax',':Country',':Email',':category',':contact_via',':Word_of_Mouth',':sweets_sweets_internet',':truck_800number',':building_systems_magazine',':Res_Build_prod_4c_ad',':thomas_register',':SBS_web_page',':mortgage_lenders',':link_from_web_page',':yellow_pages',':product_file_dir_listing',':other',':Free_House_Package_Catalog',':Information_Kit',':Kit_Payment',':Comments');">

<iREM -- If mailto is set, email a notification of the submission to the specified address -- >
<iIF COND=<iISDEF VAR="mailto">>
  <iMAIL ADDRESS=":mailto" FROM="formprocessor@adminware.com" SUBJECT=":subj">A new entry has been added:

Name:					:Name
Company:					:Company
Address:					:Address
City:					:City
State:					:State
Zip:						:Zip
Phone:					:Phone
Fax:						:Fax
Country:					:Country
Email:					:Email
category:					:category
contact_via:				:contact_via
Word_of_Mouth:				:Word_of_Mouth
sweets_sweets_internet:		:sweets_sweets_internet
truck_800number:			:truck_800number
building_systems_magazine:	:building_systems_magazine
Res_Build_prod_4c_ad:		:Res_Build_prod_4c_ad
thomas_register:			:thomas_register
SBS_web_page:				:SBS_web_page
mortgage_lenders:			:mortgage_lenders
link_from_web_page:			:link_from_web_page
yellow_pages:				:yellow_pages
product_file_dir_listing:	:product_file_dir_listing
other:					:other
Free_House_Package_Catalog:	:Free_House_Package_Catalog
Information_Kit:			:Information_Kit
Kit_Payment:				:Kit_Payment
Comments:					:Comments

</iMAIL>
</iIF>

<iREM -- If redir is set, redirect user upon completion, otherwise display generic message -- >
<iIF COND=<iISDEF VAR="redir">>
  <iREDIR URL=":redir">
<iELSE>
  Generic Message
</iIF>
