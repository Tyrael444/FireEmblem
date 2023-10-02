// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enum/GridEnums.h"
#include "GameFramework/Actor.h"
#include "Navigation/Tile/BaseTile.h"
#include "GridManager.generated.h"

class UBoxComponent;

USTRUCT()
struct FGridNestedIntArray
{
	GENERATED_BODY()

	TArray<int> Values;
};

/* Spawns the grid and all grid based arrays. 
* Holds the location on the grid of all actors and the walkability between tiles. 
* Runs pathfinding, visibility and all other grid-based code. Holds many such functions that are generally called by other classes/blueprints. 
* Also responsible for instantiating meshes.
*/
UCLASS(meta = (Tooltip = "Spawns the grid and all grid based arrays. Holds the location on the grid of all actors and the walkability between tiles. Runs pathfinding, visibility and all other grid-based code. Holds many such functions that are generally called by other blueprints. Also responsible for instantiating meshes."))
class FIREEMBLEM_API AGridManager : public AActor
{
	GENERATED_BODY()

public:

	/* defines this type as it is used by the generic A* implementation */
	typedef int FTileRef;


	/* Singleton access method */
	UFUNCTION(BlueprintCallable)
	static AGridManager* GetInstance();

	/********
	* Grid setup
	********/

	/* Scales the collision box and heightmap box to cover the entire grid */
	UFUNCTION(BlueprintCallable)
	virtual void ScaleCollisionAndHeightmapBoxes(bool bOverrideSize, const FIntPoint& aSizeOverride, FVector& outLocation, FVector& outScale);


	/********
	* Utility
	********/

	/* Converts an index to a location before GridLocations has been generated.
	* If GridLocations has been created, generally use it instead
	*/
	UFUNCTION(BlueprintCallable)
	virtual const FVector GetDisplayTileLocationFromIndex(const int32& anIndex, const FIntPoint& aSize) const;

	/* Returns all grid indexes in a specified rectangular area and offset by a specified grid index.
	* Purely math based and does not use any generated grid data
	*/
	UFUNCTION(BlueprintCallable)
	virtual TArray<int32> GetAllGridIndexesNaive(const int32& aStartIndex, const FIntPoint& aGridSize);

	/* Math expression to convert a tile index to a world location */
	UFUNCTION(BlueprintCallable)
	virtual FVector ConvertTileIndexToLocationNaive(const int32& aGridIndex) const;

	/* Convert a grid location to a world one using the grid manager transform */
	UFUNCTION(BlueprintCallable)
	virtual FVector ConvertGridLocationToWorld(const FVector& aGridLocation) const;

	/* Convert a grid location to a world one using the grid manager transform */
	virtual FVector ConvertGridLocationToWorld(const float& aX, const float& aY, const float& aZ) const;

	/* Gets a location and finds the closest corresponding location
	* Does not take overlapping tiles into account
	*/
	UFUNCTION(BlueprintCallable)
	virtual int32 ConvertLocationToIndex3DNaive(const FVector& aLocation) const;

	/* Converts a world location to a grid one */
	UFUNCTION(BlueprintCallable)
	virtual const FVector ConvertWorldLocationToGrid(const FVector& aWorldLocation) const;

	/* Rounds off a location to the closest tile center */
	UFUNCTION(BlueprintCallable)
	virtual const FVector FindClosestTileToSnapTo(const FVector& aLocation) const;

	/* Fires a line trace between two tiles, return if there is a hit */
	UFUNCTION(BlueprintCallable)
	virtual bool TraceOnGrid(const int32& aStartIndex, const int32& aTargetIndex, const ETraceTypeQuery& aTraceChannel, const float& aTraceHeight) const;

	/* Returns the world location at an index, with an offset on the Z axis */
	UFUNCTION(BlueprintCallable)
	virtual bool GetOffsetedWorldLocationAtIndex(const int32& aGridIndex, const float& anOffset, FVector& outWorldLocation) const;

	/* Return if the grid contains a specific tile, searching by index */
	UFUNCTION(BlueprintCallable)
	virtual bool ContainsTile(const int32& aTileIndex) const;

	/* Return if the grid contains a specific tile */
	virtual bool ContainsTile(const FBaseTile& aTile) const;

	/* Returns the tile at a specific index.
	* It will assume that the index is in the grid, please before calling it, ensure that the index is valid
	*/
	UFUNCTION(BlueprintCallable)
	virtual FBaseTile& GetTileFromIndex(const int32& anIndex);

	/* const version */
	virtual const FBaseTile& GetTileFromIndex(const int32& anIndex) const;

	/* Returns if a specific index is linked to a tile in the grid */
	UFUNCTION(BlueprintCallable)
	virtual bool IsIndexValid(const int32& anIndex) const;
	virtual bool IsIndexValid(const int32& aX, const int32& aY) const;

	/* Compares height difference of two tiles. Returns the appropriate edge cost between them based on the values specified. 
	* If the difference is larger than the HeightImpassableCutoff, returns -1 (indicating that the edge should be removed).
	* If the difference is lower than HeightImpassableCutoff, but higher than HeightSlowIncrement, returns a value corresponding to the height difference divided by the height slow increment.  
	*/
	UFUNCTION(BlueprintCallable)
	virtual int GetEdgeCostFromZDifference(const float& aStartZ, const float& aTargetZ) const;

	/* Given a specific tile or index, try to find the neighbour tile along a specific direction. 
	* This assume that there is a connection between the 2 tiles
	* If the index is invalid, return false; otherwise return true
	*/
	UFUNCTION(BlueprintCallable)
	virtual bool GetNeighbourUsingDirection(const int32& aTileIndex, const int32& aDirection, FBaseTile& outNeighbourTile) const;
	virtual bool GetNeighbourUsingDirection(const FBaseTile& aTile, const int32& aDirection, FBaseTile& outNeighbourTile) const;


	/********
	* Accessors
	********/

	/* Access to the grid heightmap type field */
	UFUNCTION(BlueprintCallable)
	EGridHeight GetHeighType() const;

	/* Access to the grid min height */
	UFUNCTION(BlueprintCallable)
	float GetMinHeight() const;

	/* Access to the grid max height */
	UFUNCTION(BlueprintCallable)
	float GetMaxHeight() const;

	/* Access to the default tile width */
	UFUNCTION(BlueprintCallable)
	float GetDefaultTileWidth() const;

	/* Access to the default tile mesh */
	UFUNCTION(BlueprintCallable)
	UStaticMesh* GetDefaultTileMesh() const;

	/* Returns the size of the graph (GraphSize.X * GraphSize.Y) */
	UFUNCTION(BlueprintCallable)
	int32 GetGraphSize() const;

	/* Returns the tile size */
	UFUNCTION(BlueprintCallable)
	FVector GetTileSize() const;


protected:

	/********
	* Super overrides
	********/

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& anEvent) override;
#endif


	/********
	* Grid setup
	********/

	/* Prevent the user from choosing incompatible combinations of public variables */
	UFUNCTION(BlueprintCallable)
	virtual void ValidateData();

	/* Setup the default mesh and tile size */
	UFUNCTION(BlueprintCallable)
	virtual void SetupScaleAndDefaultTiles();

	/* Calculate the TileXsize (and y size) and returns if it was a success */
	UFUNCTION(BlueprintCallable)
	virtual bool CalculateTileSize();

	/* Scale and position the collision plane. 
	* This makes individual collision volumes unecessary for flat grids, and makes it possible to place meshes in the viewport if the default tile is invisible 
	*/
	UFUNCTION(BlueprintCallable)
	virtual void SetupCollisionPlane();

	/* Scale and Position HeightmapBox. 
	* Is used to show the the maximum and minimum Z locations on which heightmap tracing is used 
	*/
	UFUNCTION(BlueprintCallable)
	virtual void SetupHeightmapBox();

	/* If EnableGridLineDisplay is true, displays a decal showing grid lines on square grids, encompassing the size of the grid */
	UFUNCTION(BlueprintCallable)
	virtual void SetupGridLineDisplay();

	/* Spawns Tile Insta nced meshes in a grid pattern based on grid size and type */
	UFUNCTION(BlueprintCallable)
	virtual bool SpawnTileGrid(bool bPrintWarning = true);

	/* Scale the AutoScalesVolumes volumes depending on the HeightmapBounds */
	UFUNCTION(BlueprintCallable)
	virtual void ScaleAutoVolumes();

	/* Container function running functions in order for creating grid locations and connecting them */
	UFUNCTION(BlueprintCallable)
	virtual void SetupGridArrays();

	UFUNCTION(BlueprintCallable)
	virtual void SetupGridCollisions();

	/* Create the vector grids that form the basis of moving between grid array indexes and world locations */
	UFUNCTION(BlueprintCallable)
	virtual bool CreateGridLocations(const int32& aStartIndex, const FIntPoint& aGridSize, const EGridHeight& aHeightType, bool bShouldPrintOnFailure = true);

	/* Create the vector grid without any height consideration */
	UFUNCTION(BlueprintCallable)
	virtual bool CreateNoHeightLocations(const int32& aStartIndex, const FIntPoint& aGridSize, bool bShouldPrintOnFailure = true);

	/* Create the vector grid with a single level height */
	UFUNCTION(BlueprintCallable)
	virtual bool CreateSingleLevelLocations(const int32& aStartIndex, const FIntPoint& aGridSize, bool bShouldPrintOnFailure = true);

	/* Create the vector grid for multiple level heights.
	* This will depend on the Min/Max heights set
	*/
	UFUNCTION(BlueprintCallable)
	virtual bool CreateMultiLevelLocations(const int32& aStartIndex, const FIntPoint& aGridSize, bool bShouldPrintOnFailure = true);

	/* Generates all grid edges, determining what tiles can be moved between and the movement cost for each edge */
	UFUNCTION(BlueprintCallable)
	virtual void GenerateGridEdges();

	/* If bUseSimpleCosts is true, adds the simple costs of all tiles to the GridSimpleCosts map.
	* By default this map is checked by any units with a pathfinding type with "simple" in its name 
	*/
	UFUNCTION(BlueprintCallable)
	virtual void GenerateSimpleCostMap();

	/* At startup, generates a map of all grid tile locations. 
	* Heightmap = false: flat grid
	* Heightmap = One Level: Uses line traces to find highest points within defined boundries that blocks PathTrace
	* Heightmap = multilevel: Keeps tracing after first hit, adding more levels to the locations map when found until outside MinHeight 
	*/
	UFUNCTION(BlueprintCallable)
	virtual void CreateLocationsAndHeightmap(const int32& aGridIndex, const FVector& aLocation);

	/* Creates an array that holds all levels stored at the different grid indexes for easy lookup */
	UFUNCTION(BlueprintCallable)
	virtual void UpdateHeightmapCache(const int32& aGridIndex);

	/* Filles the BaseEdges array with the appropriate relative indexes of neighbor tiles */
	UFUNCTION(BlueprintCallable)
	virtual TArray<FIntPoint>& SetupBaseEdges();

	/* Pregenerate Gameplay Grids: Generates some of the grids used for gameplay in the construction scripts so they won't have to load during the BeginPlay.
	* Speeds up startup, but slows down the construction script. 
	* Activate before packaging
	*/
	UFUNCTION(BlueprintCallable)
	virtual void SetupEdgesUsingTerrain(bool bPrintOnError = true);

	/* Adds edges from a tile to neighboring tiles for flat grids */
	UFUNCTION(BlueprintCallable)
	virtual void AddTileEdgesNoHeightmap(const int32& aGridIndex, bool bShouldTraceForWalls, bool bPrintOnError = true);

	UFUNCTION(BlueprintCallable)
	virtual void AddTileEdgesOneLevelHeightmap(const int32& aGridIndex, bool bShouldTraceForWalls, bool bPrintOnError = true);

	UFUNCTION(BlueprintCallable)
	virtual void AddTileEdgesMultiLevelHeightmap(const int32& aGridIndex, bool bShouldTraceForWalls, bool bPrintOnError = true);


	/********
	* Utility
	********/

	/* Takes a grid index (containing XYZ) and returns the X index */
	UFUNCTION(BlueprintCallable)
	virtual const int GetXComponent(const int32& aGridIndex) const;

	/* Takes a grid index (containing XYZ) and returns the Y index */
	UFUNCTION(BlueprintCallable)
	virtual const int GetYComponent(const int32& aGridIndex) const;

	/* Takes a grid index (containing XYZ) and returns the Z index */
	UFUNCTION(BlueprintCallable)
	virtual const int GetZComponent(const int32& aGridIndex) const;


	/********
	* Debug methods
	********/

	/* Generates grids for locations, edges etc; in construction script if PregenerateGameplayGrids is true.
	* Should only be used for debugging, and not in a packaged game.
	* Displays tile edges and indexes if specified. If changes are made to the grid by placing new tiles/terrain etc.
	* This function should be re-run for the edge array to update appropriately. */
	UFUNCTION(BlueprintCallable)
	virtual void DebugPregenerateGameplayGrids();

	/* Pregenerate gameplay grids must be enabled for this function to function. Displays the grid indexes of all tiles. */
	UFUNCTION(BlueprintCallable)
	virtual void DisplayTileIndexes();

	/* Pregenerate gameplay grids must be enabled for this function to function. Displays the edges and edge costs of all tiles. */
	UFUNCTION(BlueprintCallable)
	virtual void DisplayTileEdges();

	/* Spawns the specified text on the specified tile index */
	UFUNCTION(BlueprintCallable)
	virtual void SpawnTileDebugText(const FBaseTile& aTile, const FString& aText);


private:

	AGridManager();
	~AGridManager();

	/* Recursive function use for this CreateLocationsAndHeightmap */
	void CreateLocationsAndHeightmap_Recursive(const int32& aGridIndex, FVector& aTraceStart, FVector& aTraceEnd, FVector& aLastHitPosition);


protected:

	/********
	* Components
	********/

	/* Mesh used to populate the ground level of a grid */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid options")
	TObjectPtr<UStaticMesh> DefaultTileMesh;

	/* Default tile instance mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	TObjectPtr<UInstancedStaticMeshComponent> DefaultTile;

	/* Collision plane component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	TObjectPtr<UStaticMeshComponent> CollisionPlane;

	/* Grid height bounds */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	TObjectPtr<UBoxComponent> HeightmapBounds;

	/* Grid decal used to draw display lines, etc */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	TObjectPtr<UDecalComponent> GridDecal;

	/* Arrow mesh used to draw the edges */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default")
	TObjectPtr<UStaticMesh> EdgeArrowMesh;

	/* Instanced mesh component that will hold the arrows to draw the edges */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default")
	TObjectPtr<UInstancedStaticMeshComponent> EdgeMeshInstances;


	/********
	* Settings
	********/

	/* Defines if the default tile, and thus the initial grid, be visible */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid options")
	bool ShowDefaultTile;

	/* Shows the collision plane that handles collision for the trace when the player clicks a tile. 
	* Make it visible if your default tile is invisible to place actors easily on the grid surface.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid options")
	bool ShowCollisionPlane;

	/* Is the default tile that makes up the grid walkable? If not, individual walkable tiles must be placed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid options")
	bool IsCollisionPlaneWalkable;

	/* The size in tiles of the grid in the X and Y dimensions.
	* Set fixed limits to 999 as we won't support higher values
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid options", meta = (ClampMin = "0", ClampMax = "999"))
	FIntPoint GridSize;

	/* Auto scales volumes array */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid options")
	TArray<AVolume*> AutoScaledVolumes;

	/* Channel used to trace for walkable tiles */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid options")
	TEnumAsByte<ETraceTypeQuery> PathTraceChannel;

	/* If set to false tiles will not be connected to diagonal tiles by default */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid options")
	bool UseDiagonalMovement;

	/* Channel used to trace for collison that blocks pathfinding.
	* Used if ShouldTraceForWalls is true.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid options", meta = (EditCondition = "ShouldTraceForWalls"))
	TEnumAsByte<ETraceTypeQuery> WallTraceChannel;

	/* Toggle line display */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid line display")
	bool EnableGridLineDisplay;

	/* Line thickness that will be used on the grid decal material */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid line display", meta = (ClampMin = "0", ClampMax = "4"))
	float GridLineThickness;

	/* Color used for the grid decal material */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid line display")
	FLinearColor GridLineColor;

	/* Line opacity used by the grid decal material */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid line display", meta = (ClampMin = "0", ClampMax = "1"))
	float GridLineOpacity;

	/* Shows a bounding box displaying the maximum and minimum Z location the Grid Manager will check for walkable tiles when using heightmaps */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Procedural")
	EGridBoundingBox ShowHeightmapBoundingBox = EGridBoundingBox::HIDDEN;

	/* None = no heightmap
	* OneLevel = Traces from the sky (at MaxGridHeight) to the center of each tile once to generate a single layer heightmap
	* Multilevel = Traces from sky to each tile center, then continues downward and adds a level for each level found that is further from the previous than HeightBetweenLevels until MaxLevels or MinGridHeight is reached
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Procedural")
	EGridHeight Heightmap = EGridHeight::NONE;

	/* The height above the Grid Manager from which traces are done to find walkability. 
	* Meshes above this height will not be checked
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Procedural")
	float MaxHeight = 1000.f;

	/* The height below the Grid Manager from which traces are done to find walkability.
	* Meshes below this height will not be checked
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Procedural")
	float MinHeight = -50.f;

	/* The minimum distance that must separate two levels on a multi-level grid */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Procedural")
	float HeightBetweenLevels = 200.f;

	/* If heightmap is set to multilevel, designates the maximum number of levels that will be generated. 
	* Any levels above this will be ignored. 
	* I recommend not having this higher than the maximum number of levels you want for your map, as this causes unneccessary processing
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Procedural")
	int MaxLevels;

	/* Compares height of all adjacent tiles and sets walkability to false if the difference is more that HeightImpassableCutoff 
	and to difference/heightSlowIncrement if lower than HeightImpassableCutoff but lower that HeightSlowIncrement 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Procedural")
	bool AutoHeightBasedEdgeCosts;

	/* See AutoHeightBasedEdgeCosts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Procedural")
	float HeightSlowIncrement = 100.f;

	/* See AutoHeightBasedEdgeCosts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Procedural")
	float HeightImpassableCutoff = 100.f;

	/* If enabled, removes diagonal edges where any of the straight edges snaking to the same tile are blocked in either direction. 
	* Generally prevents units from being able to cut through wall corners during movement.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Procedural")
	bool RemoveNarrowDiagonalEdges;

	/* Automatic traces between all adjacent tiles using RangeTrace and removes the edge between tiles if the trace hits. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Procedural")
	bool ShouldTraceForWalls;

	/* The height at which the Trace for Walls function should check for walls between tiles */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Procedural")
	float WallTraceHeight = 100.f;

	/* Set the default tile width. Arbitrary value */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Miscellaneous")
	float DefaultTileWidth = 200.f;

	/* Size in X and Y dimensions of the default tile (cm) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Miscellaneous")
	FVector2f TileSize;

	/* Sets to 1000000 as the grid limits are predefined to 999 per axis */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Miscellaneous")
	int32 IndexZ = 1000000;

	/* Contains the base edges directions */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Miscellaneous")
	TArray<FIntPoint> BaseEdgesDirection;

	/* Generates some of the grids used for gameplay in the construction scripts for debugging purposes (check this along with DisplayTileIndexes and DisplayTileEdges to visualize this data in editor) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid debug")
	bool DebugDisplayPregeneratedGameplayGrids;

	/* For debugging. Displays the tile indexes of all tiles in the viewport. 
	* Pregenerate Gameplay Grids must be set to true for this to work. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid debug", meta = (EditCondition = "DebugDisplayPregeneratedGameplayGrids = true"))
	bool DebugDisplayTileIndexes;

	/* For debugging. Displays the edges of all tiles in the viewport. 
	* Pregenerate Gameplay Grids must be set to true for this to work. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config|Grid debug", meta = (EditCondition = "DebugDisplayPregeneratedGameplayGrids = true"))
	bool DebugDisplayTileEdges;

	/* This map will hold the level index for tile indexes */
	UPROPERTY(VisibleAnywhere, Category = "Grid Arrays")
	TMap<int, FGridNestedIntArray> HeightmapLevels;

	/* Contains all the tiles of the grid */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Arrays")
	TArray<FBaseTile> GridTiles;

	/* Grid size on the Z axis */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Derived")
	int GridSizeZ = 0;

private:

	/* Singleton instance of the grid manager */
	static AGridManager* Instance;
};