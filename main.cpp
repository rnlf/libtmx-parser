

#include <iostream>

#include "tmx.h"


#define DEPTH_SCALE 5


#define printf_depth( depth, format, ... ) \
	printf("%*s " format "\n", ((depth)*DEPTH_SCALE), "", __VA_ARGS__)


void printProperties(int depth, const TmxParser::TmxPropertyMap_t& map)
{
	printf_depth(depth, "%s", "<properties>");
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		printf_depth(depth+1, "%s=%s", it->first.c_str(), it->second.c_str());
	}
}


void printImageData(int depth, const TmxParser::TmxImage& tmximage)
{
	printf_depth(depth, "%s", "<image>");

	depth = depth +1;
	printf_depth(depth, "Source: %s", tmximage.source.c_str());
	printf_depth(depth, "Format: %s", tmximage.format.c_str());
	printf_depth(depth, "Width: %u", tmximage.width);
	printf_depth(depth, "Height: %u", tmximage.height);
	printf_depth(depth, "TransparentColor: %s", tmximage.transparentColor.c_str());
}


void printTileDefinition(int depth, const TmxParser::TmxTileDefinitionCollection_t& collection)
{
	for (auto it = collection.begin(); it != collection.end(); ++it)
	{
		printf_depth(depth, "%s", "<tile>");
		printf_depth(depth+1, "Id: %u", it->id);
		printProperties(depth+1, it->propertyMap);
	}
}


void printTilesets(int depth, const TmxParser::TmxTilesetCollection_t& collection)
{
	for (auto it = collection.begin(); it != collection.end(); ++it)
	{
		printf_depth(depth, "%s", "<tileset>");

		depth = depth + 1;

		printf_depth(depth, "Name: %s", (*it).name.c_str());
		printf_depth(depth, "FirstGid: %u", (*it).firstgid);
		printf_depth(depth, "Width: %u", (*it).tileWidth);
		printf_depth(depth, "Height: %u", (*it).tileHeight);
		printf_depth(depth, "MarginImage: %u", (*it).tileMarginInImage);
		printf_depth(depth, "SpaceImage: %u", (*it).tileSpacingInImage);
		printImageData(depth, (*it).image);
		printTileDefinition(depth, (*it)._tiles);
	}
}


void printLayers(int depth, const TmxParser::TmxLayerCollection_t& collection)
{
	for (auto it = collection.begin(); it != collection.end(); ++it)
	{
		printf_depth(depth, "%s", "<layer>");

		depth = depth + 1;

		printf_depth(depth, "Name: %s", it->name.c_str());
		printf_depth(depth, "Width: %u", (*it).width);
		printf_depth(depth, "Height: %u", (*it).height);
		printf_depth(depth, "Opacity: %f", (*it).opacity);
		printf_depth(depth, "Visible: %u", (*it).visible);
		printProperties(depth+1, it->propertyMap);
	}
}


void printTmxMapData(const TmxParser::TmxMap* map)
{
	int depth = 0;

	printf_depth(0, "%s", "<map>");
	depth = 1;
	printf_depth(depth, "Version: %s", map->version.c_str());
	printf_depth(depth, "Orientation: %s", map->orientation.c_str());
	printf_depth(depth, "Width: %u", map->width);
	printf_depth(depth, "Height: %u", map->height);
	printf_depth(depth, "TileWidth: %u", map->tileWidth);
	printf_depth(depth, "TileHeight: %u", map->tileHeight);
	printf_depth(depth, "BackgroundColor: %s", map->backgroundColor.c_str());
	printProperties(depth+1, map->propertyMap);
	printTilesets(depth+1, map->tilesetCollection);
	printLayers(depth+1, map->layerCollection);
}


int main()
{
	std::cout << "Hello World" << std::endl;

	TmxParser::Tmx tmx;
	std::unique_ptr<TmxParser::TmxMap> map = tmx.parseFromFile("example.tmx");

	printTmxMapData(map.get());

	return 0;
}


