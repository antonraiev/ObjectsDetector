USE [ObstacleDetectorDB]
GO

/****** Object:  Table [dbo].[Object_names]    Script Date: 08/20/2012 21:48:47 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[Object_names](
	[id] [int] IDENTITY(0,1) NOT NULL,
	[name] [varchar](50) NULL,
	[description] [varchar](300) NULL,
 CONSTRAINT [PK_Object_names] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[Object_names]  WITH CHECK ADD  CONSTRAINT [CK_Object_Length_Check] CHECK  ((len([name])<=(50) AND len([description])<=(300)))
GO

ALTER TABLE [dbo].[Object_names] CHECK CONSTRAINT [CK_Object_Length_Check]
GO


