USE [ObstacleDetectorDB]
GO

/****** Object:  StoredProcedure [dbo].[GET_SNAPSHOTS]    Script Date: 08/20/2012 21:56:12 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[GET_SNAPSHOTS]
AS
BEGIN
	SET NOCOUNT ON
	SELECT DISTINCT Snapshots.id,snapshot,width,height,datetime,snapshot_id FROM [dbo].[Snapshots] 
	LEFT OUTER JOIN [dbo].[Parts] 
	ON Snapshots.id=snapshot_id;
END

GO

