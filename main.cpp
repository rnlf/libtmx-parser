

#include <iostream>

#include "tmxparser.h"


#define DEPTH_SCALE 5


#define printf_depth( depth, format, ... ) \
	printf("%*s " format "\n", ((depth)*DEPTH_SCALE), "", __VA_ARGS__)


void printProperties(int depth, const tmxparser::TmxPropertyMap_t& map)
{
	printf_depth(depth, "%s", "<properties>");
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		printf_depth(depth+1, "%s=%s", it->first.c_str(), it->second.c_str());
	}
}


void printImageData(int depth, const tmxparser::TmxImage& tmximage)
{
	printf_depth(depth, "%s", "<image>");

	depth = depth +1;
	printf_depth(depth, "Source: %s", tmximage.source.c_str());
	printf_depth(depth, "Format: %s", tmximage.format.c_str());
	printf_depth(depth, "Width: %u", tmximage.width);
	printf_depth(depth, "Height: %u", tmximage.height);
	printf_depth(depth, "TransparentColor: %s", tmximage.transparentColor.c_str());
}


void printTileDefinition(int depth, const tmxparser::TmxTileDefinitionCollection_t& collection)
{
	for (auto it = collection.begin(); it != collection.end(); ++it)
	{
		printf_depth(depth, "%s", "<tile>");
		printf_depth(depth+1, "Id: %u", it->id);
		printProperties(depth+1, it->propertyMap);
	}
}


void printTilesets(int depth, const tmxparser::TmxTilesetCollection_t& collection)
{
	for (auto it = collection.begin(); it != collection.end(); ++it)
	{
		printf_depth(depth, "%s", "<tileset>");

		int nextdepth = depth + 1;

		printf_depth(nextdepth, "Name: %s", (*it).name.c_str());
		printf_depth(nextdepth, "FirstGid: %u", (*it).firstgid);
		printf_depth(nextdepth, "Width: %u", (*it).tileWidth);
		printf_depth(nextdepth, "Height: %u", (*it).tileHeight);
		printf_depth(nextdepth, "MarginImage: %u", (*it).tileMarginInImage);
		printf_depth(nextdepth, "SpaceImage: %u", (*it).tileSpacingInImage);
		printImageData(nextdepth, (*it).image);
		printTileDefinition(nextdepth, (*it)._tiles);
	}
}


void printLayerTiles(int depth, const tmxparser::TmxLayerTileCollection_t& collection)
{
	for (auto it = collection.begin(); it != collection.end(); ++it)
	{
		printf_depth(depth, "%s", "<tile>");

		int nextdepth = depth + 1;

		printf_depth(nextdepth, "Gid: %u", it->gid);
	}
}


void printLayers(int depth, const tmxparser::TmxLayerCollection_t& collection)
{
	for (auto it = collection.begin(); it != collection.end(); ++it)
	{
		printf_depth(depth, "%s", "<layer>");

		int nextdepth = depth + 1;

		printf_depth(nextdepth, "Name: %s", it->name.c_str());
		printf_depth(nextdepth, "Width: %u", (*it).width);
		printf_depth(nextdepth, "Height: %u", (*it).height);
		printf_depth(nextdepth, "Opacity: %f", (*it).opacity);
		printf_depth(nextdepth, "Visible: %u", (*it).visible);
		printProperties(nextdepth+1, it->propertyMap);
		printLayerTiles(nextdepth+1, it->tiles);
	}
}


void printTmxMapData(const tmxparser::TmxMap* map)
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
	printf("tmxparser::main()\n");

	tmxparser::TmxMap map;

	// test from file
	tmxparser::TmxReturn error = tmxparser::parseFromFile("example.tmx", &map);

	// test from memory
	/*FILE* fp;
	fp = fopen("example.tmx", "rb");
	fseek( fp, 0, SEEK_SET );
	fgetc( fp );
	fseek( fp, 0, SEEK_END );
	size_t size = ftell( fp );
	fseek( fp, 0, SEEK_SET );

	char* charBuffer = new char[size+1];
	size_t read = fread( charBuffer, 1, size, fp );

	tmxparser::TmxReturn error = tmxparser::parseFromMemory(charBuffer, size, &map);*/

	if (!error)
	{
		printTmxMapData(&map);
	}

	return error;
}



