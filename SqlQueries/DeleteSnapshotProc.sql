USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[DELETE_SNAPSHOT]    Script Date: 08/20/2012 21:54:54 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[DELETE_SNAPSHOT] 
@id int
AS
BEGIN
	SET NOCOUNT ON;
	DELETE FROM [dbo].[Snapshots] WHERE id=@id;
END

GO

