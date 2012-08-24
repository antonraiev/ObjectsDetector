USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[GET_MAP]    Script Date: 08/24/2012 17:41:15 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[GET_MAP]
(
@id int
)
AS
BEGIN
	SET NOCOUNT ON
	SELECT map, 
	width,height,[datetime]
	FROM [ObstacleDetectorDB].[dbo].[Maps]
	WHERE id = @id;
END

GO


