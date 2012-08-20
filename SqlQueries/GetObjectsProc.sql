USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[GET_OBJECTS]    Script Date: 08/20/2012 21:55:06 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[GET_OBJECTS]
AS
BEGIN
	SET NOCOUNT ON
	SELECT Objects.id,object,image_width,
	image_height,phys_height,name,description,name_id
	FROM Objects LEFT JOIN Object_names 
	ON Objects.name_id=Object_names.id; 
END

GO

