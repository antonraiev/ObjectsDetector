USE [ObstacleDetectorDB]
GO

/****** Object:  Table [dbo].[Scenes]    Script Date: 08/20/2012 21:50:34 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[Scenes](
	[id] [int] IDENTITY(0,1) NOT NULL,
	[scene] [varbinary](max) NULL,
	[width] [int] NULL,
	[height] [int] NULL,
	[datetime] [datetime] NULL,
	[map_id] [int] NULL,
 CONSTRAINT [PK_Scenes] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[Scenes]  WITH CHECK ADD  CONSTRAINT [FK_Scenes_Maps] FOREIGN KEY([map_id])
REFERENCES [dbo].[Maps] ([id])
ON UPDATE CASCADE
ON DELETE SET NULL
GO

ALTER TABLE [dbo].[Scenes] CHECK CONSTRAINT [FK_Scenes_Maps]
GO


