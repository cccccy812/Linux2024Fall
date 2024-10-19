COMPRESSED_DIR="/home/chelsea/Linux_Week5_Lab/compressed_files"
STUDENT_ID_FILE="/home/chelsea/Linux_Week5_Lab/student_id"
MISSING_LIST="/home/chelsea/Linux_Week5_Lab/missing_list"
WRONG_LIST="/home/chelsea/Linux_Week5_Lab/wrong_list"
ZIP_DIR="$COMPRESSED_DIR/zip_files"
RAR_DIR="$COMPRESSED_DIR/rar_files"
TAR_GZ_DIR="$COMPRESSED_DIR/tar_gz_files"
UNKNOWN_DIR="$COMPRESSED_DIR/unknown_files"

mkdir -p "$ZIP_DIR" "$RAR_DIR" "$TAR_GZ_DIR" "$UNKNOWN_DIR"

> "$MISSING_LIST"
> "$WRONG_LIST"

mapfile -t student_ids < "$STUDENT_ID_FILE"

for student_id in "${student_ids[@]}"; do
	found=0
	for file in "$COMPRESSED_DIR"/*; do
		if [[ $file == *"$student_id"* ]]; then
			found=1

			case "$file" in
				*.zip)
					mv "$file" "$ZIP_DIR"
					unzip "$ZIP_DIR/$(basename "$file")" -d "$ZIP_DIR"
					;;
				 *.rar)
                                        mv "$file" "$RAR_DIR"
                                        unrar x "$RAR_DIR/$(basename "$file")" "$RAR_DIR"
                                        ;;
				 *.tar.gz)
                                        mv "$file" "$TAR_GZ_DIR"
                                        tar -xzvf "$TAR_GZ_DIR/$(basename "$file")" -C "$TAR_GZ_DIR"
                                        ;;
				 *)
                                        mv "$file" "$UNKNOWN_DIR"
                                        echo "$student_id" >> "$WRONG_LIST"
                                        ;;
			esac
		fi
	done
	if [ $found -eq 0 ]; then	
	echo "$student_id" >> "$MISSING_LIST"
	fi
done

echo "uncompress complete"

