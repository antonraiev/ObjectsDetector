USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[ADD_OBJECT]    Script Date: 08/20/2012 21:51:46 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[ADD_OBJECT] 
	(
	@object varbinary(MAX),
	@iwidth smallint,
	@iheight smallint,
	@phys_height smallint,
	@name_id smallint
	)
AS
BEGIN
	SET NOCOUNT ON;
    INSERT INTO [dbo].[Objects]
    (object,image_width,image_height,phys_height,name_id)
    VALUES(@object,@iwidth,@iheight,@phys_height,@name_id);
END

GO


