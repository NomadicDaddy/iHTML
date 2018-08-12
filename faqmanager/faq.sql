CREATE TABLE categories (
	id int IDENTITY (1, 1) NOT NULL ,
	name varchar (50) NOT NULL 
)
GO

CREATE TABLE questions (
	id int IDENTITY (1, 1) NOT NULL ,
	cat_id int NOT NULL ,
	question text NOT NULL ,
	answer text NULL ,
	dateAsked smalldatetime NOT NULL DEFAULT (GETDATE()) ,
	dateAnswered smalldatetime NOT NULL DEFAULT (GETDATE()) ,
	viewed int NOT NULL DEFAULT (0) ,
	notifyEmail varchar (50) NULL 
)
GO

CREATE  CLUSTERED  INDEX IX_categories ON categories(id, name)
GO

CREATE  CLUSTERED  INDEX IX_questions ON questions(id, cat_id)
GO
