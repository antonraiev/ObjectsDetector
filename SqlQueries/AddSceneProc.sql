USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[ADD_SCENE]    Script Date: 08/20/2012 21:53:15 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[ADD_SCENE] 
	(
	@scene varbinary(MAX),
	@width smallint,
	@height smallint,
	@id int OUTPUT
	)
AS
BEGIN
	SET NOCOUNT ON;

    INSERT INTO [ObstacleDetectorDB].[dbo].[Scenes](scene,width,height,datetime)
    VALUES(@scene,@width,@height,CURRENT_TIMESTAMP);
    SELECT @id = IDENT_CURRENT('ObstacleDetectorDB.dbo.Scenes');
END

GO

