package com.asgmt.matwam.store.local.fact;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.room.Entity;
import androidx.room.PrimaryKey;

@Entity
public class Fact implements Parcelable {

    @PrimaryKey(autoGenerate = true)
    public Long id;

    public String label;
    public String content;

    public Fact() {}

    public static Fact create(int id, String label, String content) {
        Fact fact = new Fact();
        fact.id = (long) id;
        fact.label = label;
        fact.content = content;
        return fact;
    }

    protected Fact(Parcel in) {
        if (in.readByte() == 0) {
            id = null;
        } else {
            id = in.readLong();
        }
        label = in.readString();
        content = in.readString();
    }

    public static final Creator<Fact> CREATOR = new Creator<Fact>() {
        @Override
        public Fact createFromParcel(Parcel in) {
            return new Fact(in);
        }

        @Override
        public Fact[] newArray(int size) {
            return new Fact[size];
        }
    };

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel parcel, int i) {
        if (id == null) {
            parcel.writeByte((byte) 0);
        } else {
            parcel.writeByte((byte) 1);
            parcel.writeLong(id);
        }
        parcel.writeString(label);
        parcel.writeString(content);
    }
}
