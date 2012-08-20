USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[DELETE_SCENE]    Script Date: 08/20/2012 21:54:41 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[DELETE_SCENE] 
@id int
AS
BEGIN
	SET NOCOUNT ON;
	DELETE FROM [dbo].[Scenes] WHERE id=@id;
END

GO

