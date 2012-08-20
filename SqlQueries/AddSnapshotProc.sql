USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[ADD_SNAPSHOT]    Script Date: 08/20/2012 21:53:32 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[ADD_SNAPSHOT] 
	(
	@snapshot varbinary(MAX),
	@width smallint,
	@height smallint,
	@id int OUTPUT
	)
AS
BEGIN
	SET NOCOUNT ON;
    INSERT INTO [ObstacleDetectorDB].[dbo].[Snapshots](snapshot,width,height,datetime)
    VALUES(@snapshot,@width,@height,CURRENT_TIMESTAMP);
    SELECT @id = IDENT_CURRENT('ObstacleDetectorDB.dbo.Snapshots');
END

GO

