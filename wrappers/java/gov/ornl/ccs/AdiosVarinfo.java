// The AdiosJava.java file
package gov.ornl.ccs;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class AdiosVarinfo
{

    // Declaration of the Native (C) function
    private native int adios_inq_var(long gp, String varname);
    private native int adios_free_varinfo();
    private native double[] adios_read_var_byid(long gp, int varid, long[] start, long[] count);
    private native byte[] adios_read_var_byid_as_bytearr(long gp, int varid, long[] start, long[] count);
    private native int[] adios_read_var_byid_as_intarr(long gp, int varid, long[] start, long[] count);
    private native long[] adios_read_var_byid_as_longarr(long gp, int varid, long[] start, long[] count);
    private native float[] adios_read_var_byid_as_floatarr(long gp, int varid, long[] start, long[] count);
    private native double[] adios_read_var_byid_as_doublearr(long gp, int varid, long[] start, long[] count);

    AdiosGroup group;

    public long vp;
    public int grpid;
    public int varid;
    public int type;
    public int ndim;
    public long[] dims;
    public int timedim;
    public byte[] value;

    static
    {
        // The runtime system executes a class's static
        // initializer when it loads the class.
        System.loadLibrary("AdiosJava");
    }

    public AdiosVarinfo(AdiosGroup group)
    {
        this.group = group;
    }

    public int inq(String varname)
    {
        return adios_inq_var(group.gp, varname);
    }

    public int close()
    {
        return adios_free_varinfo();
    }

    public byte[] readAsByteArr(long[] start, long[] count)
    {
        return adios_read_var_byid_as_bytearr(group.gp, varid, start, count);
    }

    public int[] readAsIntArr(long[] start, long[] count)
    {
        return adios_read_var_byid_as_intarr(group.gp, varid, start, count);
    }

    public long[] readAsLongArr(long[] start, long[] count)
    {
        return adios_read_var_byid_as_longarr(group.gp, varid, start, count);
    }

    public float[] readAsFloatArr(long[] start, long[] count)
    {
        return adios_read_var_byid_as_floatarr(group.gp, varid, start, count);
    }

    public double[] readAsDoubleArr(long[] start, long[] count)
    {
        return adios_read_var_byid_as_doublearr(group.gp, varid, start, count);
    }

    public int readAsInt()
    {
        ByteBuffer bb = ByteBuffer.wrap(value);
        if (group.file.endianness == 0)
            bb.order(ByteOrder.LITTLE_ENDIAN);
        else
            bb.order(ByteOrder.BIG_ENDIAN);

        return bb.getInt();
    }

    public long readAsLong()
    {
        ByteBuffer bb = ByteBuffer.wrap(value);
        if (group.file.endianness == 0)
            bb.order(ByteOrder.LITTLE_ENDIAN);
        else
            bb.order(ByteOrder.BIG_ENDIAN);

        return bb.getLong();
    }

    public float readAsFloat()
    {
        ByteBuffer bb = ByteBuffer.wrap(value);
        if (group.file.endianness == 0)
            bb.order(ByteOrder.LITTLE_ENDIAN);
        else
            bb.order(ByteOrder.BIG_ENDIAN);

        return bb.getFloat();
    }

    public double readAsDouble()
    {
        ByteBuffer bb = ByteBuffer.wrap(value);
        if (group.file.endianness == 0)
            bb.order(ByteOrder.LITTLE_ENDIAN);
        else
            bb.order(ByteOrder.BIG_ENDIAN);

        return bb.getDouble();
    }

    public String toString()
    {
        StringBuilder result = new StringBuilder();
        String NEW_LINE = System.getProperty("line.separator");

        result.append(this.getClass().getName() + " Object {" + NEW_LINE);
        result.append(" vp: " + vp + NEW_LINE);
        result.append(" grpid: " + grpid + NEW_LINE);
        result.append(" varid: " + varid + NEW_LINE);
        result.append(" type: " + type + NEW_LINE);
        result.append(" ndim: " + ndim + NEW_LINE);
        result.append(" dims.length: " + dims.length + NEW_LINE);
        if (dims.length > 0) {
            for (int i = 0; i < dims.length; i++) {
                result.append(" dims[" + i + "]: " + dims[i] + NEW_LINE);
            }
        }
        result.append(" timedim: " + timedim + NEW_LINE);
        result.append("}");

        return result.toString();
    }
}
