class SCR_WhereAmIUI : SCR_MapUIBaseComponent
{
	protected Widget m_widget;
	protected SCR_MapToolEntry m_ToolMenuEntry;
	protected ImageWidget m_DirectionImage;
	protected bool m_showDirection = true;

	override void Update(float timeSlice)
	{
		if (!m_widget)
			return;

		ChimeraCharacter player = ChimeraCharacter.Cast(SCR_PlayerController.GetLocalControlledEntity());
		if (!player)
		{
			m_widget.RemoveFromHierarchy();
			return;
		}

		vector posPlayer = player.GetOrigin();

		float x, y;
		m_MapEntity.WorldToScreen(posPlayer[0], posPlayer[2], x, y, true);

		x = GetGame().GetWorkspace().DPIUnscale(x);
		y = GetGame().GetWorkspace().DPIUnscale(y);

		FrameSlot.SetPos(m_widget, x, y);
		
		vector rotPlayer = player.GetYawPitchRoll();

		if(m_DirectionImage)
		{
			m_DirectionImage.SetRotation(rotPlayer[0]);
		}
	}

	override void OnMapOpen(MapConfiguration config)
	{
		super.OnMapOpen(config);

		if (m_widget)
		{
			return;
		}

		m_widget = GetGame().GetWorkspace().CreateWidgets("{3513CA0C0C83D2E3}UI/layouts/GPS/PlayerMapIndicator.layout", m_RootWidget);
		m_DirectionImage = ImageWidget.Cast(m_widget.FindAnyWidget("LineImage"));
		
		if (m_showDirection)
		{
			m_DirectionImage.SetVisible(true);
		}
	}

	//------------------------------------------------------------------------------------------------
	override void Init()
	{
		SCR_MapToolMenuUI toolMenu = SCR_MapToolMenuUI.Cast(m_MapEntity.GetMapUIComponent(SCR_MapToolMenuUI));
		if (toolMenu)
		{
			m_ToolMenuEntry = toolMenu.RegisterToolMenuEntry("{14A14368AE7FA04D}UI/Textures/Icons/PlayerMarker.imageset", "PlayerMarker", 99);
			m_ToolMenuEntry.m_OnClick.Insert(ZoomInOnPlayer);
		}
		
		Resource holder = BaseContainerTools.LoadContainer("{44EFCF9D49290924}Configs/Map/WhereAmI.conf");
		if (!holder)
		{
			return;
		}
		
		SCR_WhereAmIConfig config = SCR_WhereAmIConfig.Cast(BaseContainerTools.CreateInstanceFromContainer(holder.GetResource().ToBaseContainer()));
		if (config)
		{
			m_showDirection = config.m_bShowDirection;
		}
	}

	//------------------------------------------------------------------------------------------------
	protected void ZoomInOnPlayer()
	{
		ChimeraCharacter player = ChimeraCharacter.Cast(SCR_PlayerController.GetLocalControlledEntity());
		if (!player)
		{
			return;
		}

		vector posPlayer = player.GetOrigin();

		vector mapSize = m_MapEntity.GetMapWidget().GetSizeInUnits();
		float zoomVal = mapSize[0] / (mapSize[0] * (m_MapEntity.GetMapWidget().PixelPerUnit() * 1.5));

		m_MapEntity.ZoomPanSmooth(zoomVal,posPlayer[0],posPlayer[2]);
	}
};
