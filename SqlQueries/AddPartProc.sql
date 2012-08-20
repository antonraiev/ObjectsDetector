USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[ADD_PART]    Script Date: 08/20/2012 21:52:48 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[ADD_PART]
	@scene_id int,
	@snapshot_id int
AS
BEGIN
	SET NOCOUNT ON;
	INSERT INTO [dbo].[Parts](scene_id,snapshot_id)
	VALUES(@scene_id,@snapshot_id);
END

GO


