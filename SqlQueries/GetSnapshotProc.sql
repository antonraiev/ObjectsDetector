USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[GET_SNAPSHOT]    Script Date: 08/20/2012 21:55:58 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[GET_SNAPSHOT]
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
	SELECT snapshot,--@datetime=[datetime], 
	width,height,[datetime]
	FROM [ObstacleDetectorDB].[dbo].[Snapshots]
	WHERE id=@id;
END

GO

