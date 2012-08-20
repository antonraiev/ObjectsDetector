USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[CHANGE_OBJECT_DESCRIPTION]    Script Date: 08/20/2012 21:53:57 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[CHANGE_OBJECT_DESCRIPTION] 
	@id int,
	@name varchar(50),
	@description varchar(300)
AS
BEGIN
	SET NOCOUNT ON;
	UPDATE [dbo].[Object_names]
	SET name=@name,
	description=@description
	WHERE id=@id;
END

GO

