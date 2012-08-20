USE [ObstacleDetectorDB]
GO

/****** Object:  Table [dbo].[Snapshots]    Script Date: 08/20/2012 21:51:25 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[Snapshots](
	[id] [int] IDENTITY(0,1) NOT NULL,
	[snapshot] [varbinary](max) NULL,
	[width] [smallint] NULL,
	[height] [smallint] NULL,
	[datetime] [datetime] NULL,
 CONSTRAINT [PK_Snapshots] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[Snapshots]  WITH CHECK ADD  CONSTRAINT [CK_Snapshots] CHECK  (([width]<=(2048) AND [height]<=(2048)))
GO

ALTER TABLE [dbo].[Snapshots] CHECK CONSTRAINT [CK_Snapshots]
GO

