USE [ObstacleDetectorDB]
GO

/****** Object:  Table [dbo].[Maps]    Script Date: 08/20/2012 21:45:25 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[Maps](
	[id] [int] IDENTITY(0,1) NOT NULL,
	[map] [varbinary](max) NULL,
	[width] [int] NULL,
	[height] [int] NULL,
	[datetime] [datetime] NULL,
 CONSTRAINT [PK_Maps] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO


