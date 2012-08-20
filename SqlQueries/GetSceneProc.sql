USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[GET_SCENE]    Script Date: 08/20/2012 21:55:35 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[GET_SCENE]
(
@id int
--@snapshot varbinary(MAX) OUTPUT,
--@width smallint OUTPUT,
--@height smallint OUTPUT
--@datetime datetime OUTPUT 
)
AS
BEGIN
	SET NOCOUNT ON
	SELECT scene,--@datetime=[datetime], 
	width,height,[datetime]
	FROM [ObstacleDetectorDB].[dbo].[Scenes]
	WHERE id=@id;
END

GO

