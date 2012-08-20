USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[GET_SCENES]    Script Date: 08/20/2012 21:55:45 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[GET_SCENES]
AS
BEGIN
	SET NOCOUNT ON
	SELECT * FROM [dbo].[Scenes]; 
END

GO

