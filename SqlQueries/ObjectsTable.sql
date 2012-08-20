USE [ObstacleDetectorDB]
GO

/****** Object:  Table [dbo].[Objects]    Script Date: 08/20/2012 21:49:38 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_PADDING ON
GO

CREATE TABLE [dbo].[Objects](
	[id] [int] IDENTITY(0,1) NOT NULL,
	[object] [varbinary](max) NULL,
	[image_width] [int] NULL,
	[image_height] [int] NULL,
	[phys_height] [int] NULL,
	[name_id] [int] NOT NULL,
 CONSTRAINT [PK_Objects] PRIMARY KEY CLUSTERED 
(
	[id] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO

SET ANSI_PADDING OFF
GO

ALTER TABLE [dbo].[Objects]  WITH CHECK ADD  CONSTRAINT [FK_Objects_Object_names] FOREIGN KEY([name_id])
REFERENCES [dbo].[Object_names] ([id])
ON UPDATE CASCADE
ON DELETE CASCADE
GO

ALTER TABLE [dbo].[Objects] CHECK CONSTRAINT [FK_Objects_Object_names]
GO

ALTER TABLE [dbo].[Objects]  WITH CHECK ADD  CONSTRAINT [CK_Objects] CHECK  (([phys_height]>(0)))
GO

ALTER TABLE [dbo].[Objects] CHECK CONSTRAINT [CK_Objects]
GO


