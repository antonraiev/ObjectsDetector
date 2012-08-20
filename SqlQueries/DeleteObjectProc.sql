USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[DELETE_OBJECT]    Script Date: 08/20/2012 21:54:13 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[DELETE_OBJECT] 
@id int
AS
BEGIN
	SET NOCOUNT ON;
	DELETE FROM [dbo].[Objects] WHERE id=@id;
END

GO

