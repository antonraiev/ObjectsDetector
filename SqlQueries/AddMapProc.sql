USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[ADD_MAP]    Script Date: 08/24/2012 17:31:06 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[ADD_MAP] 
	(
	@map varbinary(MAX),
	@width smallint,
	@height smallint,
	@id int OUTPUT
	)
AS
BEGIN
	SET NOCOUNT ON;

    INSERT INTO [ObstacleDetectorDB].[dbo].[Maps](map,width,height,datetime)
    VALUES(@map,@width,@height,CURRENT_TIMESTAMP);
    SELECT @id = IDENT_CURRENT('ObstacleDetectorDB.dbo.Maps');
END

GO


