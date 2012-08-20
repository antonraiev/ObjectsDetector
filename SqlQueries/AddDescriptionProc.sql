USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[ADD_OBJECT_DESCRIPTION]    Script Date: 08/20/2012 21:52:24 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[ADD_OBJECT_DESCRIPTION] 
	-- Add the parameters for the stored procedure here
	@name varchar(50),
	@description varchar(300)
AS
BEGIN
	SET NOCOUNT ON;
	INSERT INTO [dbo].[Object_names](name,description) VALUES(@name,@description);
END

GO

