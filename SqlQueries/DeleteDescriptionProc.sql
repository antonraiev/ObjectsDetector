USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[DELETE_OBJECT_DESCRIPTION]    Script Date: 08/20/2012 21:54:30 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[DELETE_OBJECT_DESCRIPTION] 
@id int
AS
BEGIN
	SET NOCOUNT ON;
	DELETE FROM [dbo].[Object_names] WHERE id=@id;
END

GO
